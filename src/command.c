#include "command.h"
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

void sendCmd(int fd, char const* fmt, ...) {
	char cmd[CMD_LEN];
	int sz;
	va_list vp;
	va_start(vp, fmt);
	sz = vsnprintf(&cmd[0], CMD_LEN, fmt, vp);
	va_end(vp);
	if(sz > CMD_LEN) {
		fprintf(stderr, "Warning: truncated command to \"%s\" - not sending\n", cmd);
	} else {
		write(fd, (void*)cmd, sz);
	}
}
