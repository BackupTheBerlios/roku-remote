#ifndef COMMAND_H__
#define COMMAND_H__

#define CMD_LEN 256

void sendCmd(int fd, char const* fmt, ...);

#endif
