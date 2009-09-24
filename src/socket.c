/*
 * Part of roku-remote
 *
 * Copyright (c) 2009 Thomas Spurden
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "socket.h"
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <malloc.h>
#include <string.h>

void fdInit(struct fdPoll *fds) {
	FD_ZERO(&fds->read);
	FD_ZERO(&fds->write);
	FD_ZERO(&fds->except);
	fds->fds=NULL;
}

void fdAdd(struct fdPoll *fds, int fd, uint8_t set, int (*callback)(uint8_t, int, void*),void *param) {
	struct fdList *d=(struct fdList*)malloc(sizeof(struct fdList));
	/*fprintf(stderr,"[%d] Adding to polled sockets mask 0x%x\n",fd,set);*/
	d->next=fds->fds;
	d->fd=fd;
	d->callback=callback;
	d->param=param;
	fds->fds=d;
	if(set & WAIT_READ)
		FD_SET(fd,&fds->read);
	if(set & WAIT_WRITE)
		FD_SET(fd,&fds->write);
	if(set & WAIT_EXCEPT)
		FD_SET(fd,&fds->except);
}

void printError(const char *msg) {
	fprintf(stderr,"%s: %s\n",msg,strerror(errno));
}

int createConnectSocket(const char *hostname, uint16_t port) {
	int sock;
	struct sockaddr_in name;
	struct hostent *hostinfo;
	sock=socket(PF_INET,SOCK_STREAM,0);
	if(sock==-1) {
		printError("Could not create socket");
		return -1;
	}
	name.sin_family=AF_INET;
	name.sin_port=htons(port);
	hostinfo=gethostbyname(hostname);
	if(!hostinfo) {
		printError("Could not lookup hostname");
		return -1;
	}
	name.sin_addr=*(struct in_addr *)hostinfo->h_addr_list[0];
	if(connect(sock,(struct sockaddr *)&name,sizeof(name))==-1) {
		printError("Could not connect");
		return -1;
	}
	return sock;
}

int createListenSocket(uint16_t port) {
	int sock,flags;
	struct sockaddr_in name;
	sock=socket(PF_INET,SOCK_STREAM,0);
	if(sock==-1) {
		printError("Could not create socket");
		return -1;
	}
	flags=fcntl(sock,F_GETFD);
	if(flags==-1) {
		printError("Could not get flags on socket");
		return -1;
	}
	if(fcntl(sock,F_SETFD,flags | O_NONBLOCK)==-1) {
		printError("Could not set flags on socket");
		return -1;
	}
	name.sin_family=AF_INET;
	name.sin_port=htons(port);
	name.sin_addr.s_addr=htonl(INADDR_ANY);
	if(bind(sock,(struct sockaddr *)&name,sizeof(name))==-1) {
		printError("Could not bind socket to address");
		return -1;
	}
	if(listen(sock,8)==-1) {
		printError("Could not make the damn socket listen");
		return -1;
	}
	return sock;
}

int acceptConnection(int sock) {
	return accept(sock,NULL,NULL);
}

int closeSocket(int sock) {
	/*fprintf(stderr,"[%d] Socket is closing.\n",sock);*/
	if(shutdown(sock,SHUT_RDWR)==-1) {
		printError("Could not shutdown socket");
	}
	return close(sock);
}

int pollSockets(struct fdPoll *fds) {
	fd_set write=fds->write,read=fds->read,except=fds->except;
	struct fdList *cur=fds->fds;
	struct fdList **prev=&fds->fds;
	int tmpfd, tmpret;
	void *tmpparam;
	uint8_t mask;
	if(select(FD_SETSIZE,&read,&write,&except,NULL)<=0) {
		printError("select call failed");
		return 1;
	}
	while(cur!=NULL) {
		/*fprintf(stderr,"Checking fd %p [%d]\n", (void*)cur, cur->fd);*/
		mask=0;
		if(FD_ISSET(cur->fd,&read)) {
			mask=WAIT_READ;
		}
		if(FD_ISSET(cur->fd,&write))
			mask|=WAIT_WRITE;
		if(FD_ISSET(cur->fd,&except))
			mask|=WAIT_EXCEPT;
		/*fprintf(stderr,"Mask %x\n",mask);*/

		if(mask) {
			tmpfd=cur->fd;
			tmpparam=cur->param;
			/*fprintf(stderr,"[%d] Calling callback mask=0x%x\n",cur->fd,mask);*/
			tmpret=cur->callback(mask,tmpfd,tmpparam);
			if(tmpret) {
				FD_CLR(cur->fd,&fds->read);
				FD_CLR(cur->fd,&fds->write);
				FD_CLR(cur->fd,&fds->except);
				*prev=cur->next;
				/*fprintf(stderr,"[%d] Deleting socket from poll list\n",cur->fd);*/
				free(cur);
				cur=*prev;
			} else {
				prev=&cur->next;
				cur=cur->next;
			}
		} else {
			prev=&cur->next;
			cur=cur->next;
		}
	}
	return 0;
}
