%{

#include "keys.h"
#include "command.h"
#include "sketch.h"
#include "socket.h"

int fd;
int quit = 0;
int quitOnRead = 0;
int echoSoundbridge = 0;

/* If this is set very high then key presses might not be processed
 * straight away */
#define PARSE_BLOCK_LEN 8
#define STDIN_BLOCK_LEN 32
#define MAX_LINE_LEN 256

#define TOK_CMD	(Key_NumKeys_)
#define TOK_END (Key_NumKeys_ + 1)

struct fdPoll fds;

struct {
	size_t max;
	size_t bytesRead;
	void* buf;
} readNet;

struct {
	size_t bytesRead;
	char buf[STDIN_BLOCK_LEN];

	int fullLine;
	size_t linePtr;
	char line[MAX_LINE_LEN];
} readStdin;

#define YY_INPUT(yy_buf, yy_result, yy_max) \
{ \
	readNet.buf = (yy_buf); \
	readNet.max = (yy_max); \
	do { \
		pollSockets(&fds); \
		if(quit) { \
			close(fd); \
			exit(EXIT_FAILURE); \
		} \
		if(readStdin.bytesRead > 0) { \
			size_t i; \
			for(i = 0; i < readStdin.bytesRead; i++) { \
				if(readStdin.buf[i] == '\n') { \
					readStdin.line[readStdin.linePtr++] = '\n'; \
					readStdin.line[readStdin.linePtr] = '\0'; \
					readStdin.fullLine = 1; \
				} else { \
					if(readStdin.linePtr == MAX_LINE_LEN) { \
						fprintf(stderr, "Maximum line length reached, discarding"); \
						readStdin.linePtr = 0; \
					} \
					readStdin.line[readStdin.linePtr++] = readStdin.buf[i]; \
				} \
			} \
			readStdin.bytesRead = 0; \
		} \
	} while(readNet.bytesRead <= 0); \
	(yy_result) = readNet.bytesRead; \
	readNet.bytesRead = 0; \
}

%}

%option noyywrap

%%

"irman: CK_SELECT"				{ return CK_SELECT; }
"irman: CK_NORTH"				{ return CK_NORTH; }
"irman: CK_SOUTH"				{ return CK_SOUTH; }
"irman: CK_WEST"				{ return CK_WEST; }
"irman: CK_EAST"				{ return CK_EAST; }
"irman: CK_PLAY"				{ return CK_PLAY; }
"irman: CK_PAUSE"				{ return CK_PAUSE; }
"irman: CK_STOP"				{ return CK_STOP; }
"irman: CK_NEXT"				{ return CK_NEXT; }
"irman: CK_PREVIOUS"				{ return CK_PREVIOUS; }
"irman: CK_MENU"				{ return CK_MENU; }
"irman: CK_EXIT"				{ return CK_EXIT; }
"irman: CK_POWER"				{ return CK_POWER; }
"irman: CK_POWER_ON"				{ return CK_POWER_ON; }
"irman: CK_POWER_OFF"				{ return CK_POWER_OFF; }
"irman: CK_SEARCH"				{ return CK_SEARCH; }
"irman: CK_ADD"					{ return CK_ADD; }
"irman: CK_SHUFFLE"				{ return CK_SHUFFLE; }
"irman: CK_REPEAT"				{ return CK_REPEAT; }
"irman: CK_VOLUME_UP"				{ return CK_VOLUME_UP; }
"irman: CK_VOLUME_DOWN"				{ return CK_VOLUME_DOWN; }
"irman: CK_BRIGHTNESS"				{ return CK_BRIGHTNESS; }
"irman: CK_ROTARY_CLOCKWISE"			{ return CK_ROTARY_CLOCKWISE; }
"irman: CK_ROTARY_COUNTERCLOCKWISE"		{ return CK_ROTARY_COUNTERCLOCKWISE; }
"irman: CK_ROTARY_SWITCH"			{ return CK_ROTARY_SWITCH; }
"irman: CK_PRESET1"				{ return CK_PRESET1; }
"irman: CK_PRESET2"				{ return CK_PRESET2; }
"irman: CK_PRESET3"				{ return CK_PRESET3; }
"irman: CK_PRESET4"				{ return CK_PRESET4; }
"irman: CK_PRESET5"				{ return CK_PRESET5; }
"irman: CK_PRESET6"				{ return CK_PRESET6; }
"irman: CK_SNOOZE"				{ return CK_SNOOZE; }
"irman: CK_SOURCE"				{ return CK_SOURCE; }
"irman: CK_SCAN_UP"				{ return CK_SCAN_UP; }
"irman: CK_SCAN_DOWN"				{ return CK_SCAN_DOWN; }
"irman: CK_GROUP"				{ return CK_GROUP; }
"irman: CK_ALARM"				{ return CK_ALARM; }
"irman: CK_PLAYLISTS"				{ return CK_PLAYLISTS; }
"irman: CK_BROWSE_ARTISTS"			{ return CK_BROWSE_ARTISTS; }
"irman: CK_BROWSE_ALBUMS"			{ return CK_BROWSE_ALBUMS; }
"irman: CK_BROWSE_SONGS"			{ return CK_BROWSE_SONGS; }
"irman: CK_BROWSE_GENRES"			{ return CK_BROWSE_GENRES; }
"irman: CK_BROWSE_COMPOSERS"			{ return CK_BROWSE_COMPOSERS; }
"irman: CK_PRESET_A1"				{ return CK_PRESET_A1; }
"irman: CK_PRESET_A2"				{ return CK_PRESET_A2; }
"irman: CK_PRESET_A3"				{ return CK_PRESET_A3; }
"irman: CK_PRESET_A4"				{ return CK_PRESET_A4; }
"irman: CK_PRESET_A5"				{ return CK_PRESET_A5; }
"irman: CK_PRESET_A6"				{ return CK_PRESET_A6; }
"irman: CK_PRESET_B1"				{ return CK_PRESET_B1; }
"irman: CK_PRESET_B2"				{ return CK_PRESET_B2; }
"irman: CK_PRESET_B3"				{ return CK_PRESET_B3; }
"irman: CK_PRESET_B4"				{ return CK_PRESET_B4; }
"irman: CK_PRESET_B5"				{ return CK_PRESET_B5; }
"irman: CK_PRESET_B6"				{ return CK_PRESET_B6; }
"irman: CK_PRESET_C1"				{ return CK_PRESET_C1; }
"irman: CK_PRESET_C2"				{ return CK_PRESET_C2; }
"irman: CK_PRESET_C3"				{ return CK_PRESET_C3; }
"irman: CK_PRESET_C4"				{ return CK_PRESET_C4; }
"irman: CK_PRESET_C5"				{ return CK_PRESET_C5; }
"irman: CK_PRESET_C6"				{ return CK_PRESET_C6; }
"irman: CK_INTERNET_RADIO"			{ return CK_INTERNET_RADIO; }
"irman: CK_FM_RADIO"				{ return CK_FM_RADIO; }
"irman: CK_AM_RADIO"				{ return CK_AM_RADIO; }
"irman: CK_LAST_MUSIC_SERVER"			{ return CK_LAST_MUSIC_SERVER; }
"irman: CK_VOLUME_50"				{ return CK_VOLUME_50; }
"irman: CK_BROWSE"				{ return CK_BROWSE; }
"irman: CK_PURPLE"				{ return CK_PURPLE; }
"irman: CK_PRESET1_IR"				{ return CK_PRESET1_IR; }
"irman: CK_PRESET2_IR"				{ return CK_PRESET2_IR; }
"irman: CK_PRESET3_IR"				{ return CK_PRESET3_IR; }
"irman: CK_PRESET4_IR"				{ return CK_PRESET4_IR; }
"irman: CK_PRESET5_IR"				{ return CK_PRESET5_IR; }
"irman: CK_PRESET6_IR"				{ return CK_PRESET6_IR; }

.|\n						{ if(echoSoundbridge) printf("%s", yytext); }

<<EOF>>						return TOK_END;

%%

#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/XF86keysym.h>
#include <X11/extensions/XTest.h>

static int keys[Key_NumKeys_] = {
	[CK_POWER] = XF86XK_Standby,
	[CK_BRIGHTNESS] = XF86XK_MonBrightnessDown,

	[CK_MENU] = XK_F1,
	[CK_SEARCH] = XK_F2,
	[CK_EXIT] = XK_F3,

	[CK_NORTH] = XK_Up,
	[CK_SOUTH] = XK_Down,
	[CK_EAST] = XK_Right,
	[CK_WEST] = XK_Left,
	[CK_SELECT] = XK_F11,

	[CK_NEXT] = XK_F4,
	[CK_PLAY] = XK_F5,
	[CK_PREVIOUS] = XK_F6,

	[CK_VOLUME_UP] = XF86XK_AudioRaiseVolume,
	[CK_VOLUME_DOWN] = XF86XK_AudioLowerVolume,

	[CK_PAUSE] = XK_F7,
	[CK_SHUFFLE] = XK_F8,
	[CK_ADD] = XK_F9,
	[CK_REPEAT] = XK_F10,
};

Display* dpy;

static void generateEvent(int keycode) {
	unsigned int key = XKeysymToKeycode(dpy, keycode);
	XTestFakeKeyEvent(dpy, key, 1, CurrentTime);
	XTestFakeKeyEvent(dpy, key, 0, CurrentTime);
	XFlush(dpy);
	XSync(dpy, False);
}

static int readNetCB(uint8_t mask, int fd, void* arg) {
	if(mask & WAIT_READ) {
		readNet.bytesRead = read(fd, (void*)readNet.buf, PARSE_BLOCK_LEN > readNet.max ? readNet.max : PARSE_BLOCK_LEN);
	}
	if(mask & WAIT_WRITE && readStdin.fullLine) {
		fprintf(stderr, "Sending line \"%s\" to [%d]", readStdin.line, fd);
		write(fd, (void*)readStdin.line, readStdin.linePtr);
		readStdin.linePtr = 0;
		readStdin.fullLine = 0;
	}
	return 0;
}

static int readStdinCB(uint8_t mask, int fd, void* arg) {
	if(mask & WAIT_READ) {
		if(quitOnRead) {
			quit = 1;
		}
		readStdin.bytesRead = read(fd, (void*)readStdin.buf, STDIN_BLOCK_LEN);
	} else if(mask & WAIT_EXCEPT) {
		quit = 1;
	}
	return 0;
}

int main(int argc, char** argv) {
	int tok;
	char* address;
	int sendCmds = 0;

	if(argc < 2 || argc > 4) {
		printf("Usage: irman [-s] [-q] [-e] <ip>\n");
		printf(" -s Send lines read from stdin to the soundbridge\n");
		printf(" -q Quit when anything is read from stdin\n");
		printf(" -e Echo stuff read from the soundbrige\n");
		printf("Obviously -q and -s are mutually exclusive\n");
		return EXIT_FAILURE;
	}
	{
		unsigned int i;
		for(i = 1; i < argc; i++) {
			if(strcmp(argv[i], "-s") == 0) {
				sendCmds = 1;
			} else if(strcmp(argv[i], "-q") == 0) {
				quitOnRead = 1;
			} else if(strcmp(argv[i], "-e") == 0) {
				echoSoundbridge = 1;
			}
		}
		address = argv[argc - 1];
	}

	fdInit(&fds);

	fd = createConnectSocket(address, 4444);
	if(fd == -1) {
		return 1;
	}

	fprintf(stderr, "Connected to %s\n", address);

	sendCmd(fd, "irman intercept\n");

	dpy = XOpenDisplay(0);
	if(dpy == NULL) {
		fprintf(stderr, "Could not open X display\n");
		return -1;
	}

	fprintf(stderr, "Opened X display\n");

	readNet.bytesRead = 0;

	readStdin.bytesRead = 0;
	readStdin.linePtr = 0;
	readStdin.fullLine = 0;

	fdAdd(&fds, fd, sendCmds ? (WAIT_READ | WAIT_WRITE) : WAIT_READ, &readNetCB, NULL);
	fdAdd(&fds, 0, (sendCmds || quitOnRead) ? (WAIT_READ | WAIT_EXCEPT) : WAIT_EXCEPT, &readStdinCB, NULL);

	while((tok = yylex()) != TOK_END) {
		if(keys[tok]) {
			generateEvent(keys[tok]);
		} else {
			printf("%s\n", keySym[tok]);
		}
	}

	XCloseDisplay(dpy);

	return EXIT_SUCCESS;
}
