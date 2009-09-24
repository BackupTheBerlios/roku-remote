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

#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <stdint.h>
#include <sys/select.h>

#define WAIT_READ	0x01
#define WAIT_WRITE	0x02
#define WAIT_EXCEPT	0x04

struct fdList {
	int fd;
	int (*callback)(uint8_t, int, void*);
	void *param;
	struct fdList *next;
};

struct fdPoll {
	struct fdList *fds;
	fd_set read,write,except;
};

void fdInit(struct fdPoll *fds);
void fdAdd(struct fdPoll *fds, int fd, uint8_t set, int (*callback)(uint8_t, int, void *), void *param);
void printError(const char *msg);
int createConnectSocket(const char *hostname, uint16_t port);
int createListenSocket(uint16_t port);
int acceptConnection(int sock);
int closeSocket(int sock);
int pollSockets(struct fdPoll *fds);

#endif
