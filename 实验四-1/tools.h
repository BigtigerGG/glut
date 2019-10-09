#ifndef TOOLS_H
#define TOOLS_H

#include <gl/glut.h>
#include <stdio.h>
#include "gpoint2.h"
#include "grect2.h"

void gltLine2i(int x0, int y0, int x1, int y1);

void gltRect2i(int x0, int y0, int x1, int y1);

void gltLine2d(double x0, double y0, double x1, double y1);

void gltRect2d(double x0, double y0, double x1, double y1);

void gltRasterText(double x, double y, const char *text, 
                   void *font = GLUT_BITMAP_8_BY_13);

bool gltLineClip2d(GPoint2d &pt0, GPoint2d &pt1, const GRect2d &rc);
                   
#endif
