#ifndef GLTOOLS_H
#define GLTOOLS_H

#include <gl/glut.h>
#include <stdio.h>

void gltLine2i(int x0, int y0, int x1, int y1);

void gltRect2i(int x0, int y0, int x1, int y1);

void gltLine2d(double x0, double y0, double x1, double y1);

void gltRect2d(double x0, double y0, double x1, double y1);

void gltRasterText(double x, double y, const char *text, 
                   void *font = GLUT_BITMAP_8_BY_13);
                   
#endif
