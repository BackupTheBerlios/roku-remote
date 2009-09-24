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
