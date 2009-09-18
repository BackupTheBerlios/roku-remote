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
