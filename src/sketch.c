#include "sketch.h"
#include "command.h"

void sketchFillRect(int fd, unsigned int x, unsigned int y, unsigned int w, unsigned int h) {
	sendCmd(fd, "rect %u %u %u %u\n", x, y, w, h);
}

void sketchRect(int fd, unsigned int x, unsigned int y, unsigned int w, unsigned int h) {
	sendCmd(fd, "framerect %u %u %u %u\n", x, y, w, h);
}

void sketchPoint(int fd, unsigned int x, unsigned int y) {
	sendCmd(fd, "point %u %u\n", x, y);
}

void sketchLine(int fd, int x1, int y1, int x2, int y2) {
	sendCmd(fd, "line %i %i %i %i\n", x1, y1, x2, y2);
}

void sketchBlit(int fd, int srcX, int srcY, int srcH, int srcW, int destX, int destY) {
	sendCmd(fd, "blit %i %i %i %i %i %i\n", destX, destY, srcX, srcY, srcW, srcH);
}

void sketchSlide(int fd, int pixels, unsigned int times) {
	sendCmd(fd, "slide %i %u\n", pixels, times);
}

void sketchFont(int fd, unsigned int fontNum) {
	sendCmd(fd, "font %u\n", fontNum);
}

void sketchColor(int fd, int pen) {
	sendCmd(fd, "color %u\n", pen ? 0 : 1);
}

void sketchTextCentred(int fd, char const* text, int x, int y, int centreX, int centreY) {
	if(centreX && centreY) {
		sendCmd(fd, "text c c \"%s\"\n", text);
	} else if(centreX) {
		sendCmd(fd, "text c %i \"%s\"\n", y, text);
	} else if(centreY) {
		sendCmd(fd, "text %i c \"%s\"\n", x, text);
	} else {
		sendCmd(fd, "text %i %i \"%s\"\n", x, y, text);
	}
}

void sketchText(int fd, char const* text, int x, int y) {
	sendCmd(fd, "text %i %i \"%s\"\n", x, y, text);
}

void sketchClear(int fd) {
	sendCmd(fd, "clear\n");
}

void sketchStart(int fd) {
	sendCmd(fd, "sketch\n");
}

void sketchStop(int fd) {
	sendCmd(fd, "quit\n");
}
