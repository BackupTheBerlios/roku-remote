#ifndef SKETCH_H__
#define SKETCH_H__

void sketchFillRect(int, unsigned int x, unsigned int y, unsigned int w, unsigned int h);
void sketchRect(int, unsigned int x, unsigned int y, unsigned int w, unsigned int h);
void sketchPoint(int, unsigned int x, unsigned int y);
void sketchLine(int, int x1, int y1, int x2, int y2);
void sketchBlit(int, int srcX, int srcY, int srcH, int srcW, int destX, int destY);
void sketchSlide(int, int pixels, unsigned int times);
void sketchFont(int, unsigned int fontNum);
void sketchColor(int, int pen);
void sketchText(int, char const* text, int x, int y);
void sketchTextCentred(int, char const* text, int x, int y, int centreX, int centreY);
void sketchClear(int);
void sketchStart(int);
void sketchStop(int);

#endif
