#ifndef GLTOOLS_H
#define GLTOOLS_H

#include <gl/glut.h>
#include <stdio.h>
#include "gpoint3d.h"

void gltBeginRasterText(int w, int h);

void gltRasterText(double x, double y, const char *text, 
                   void *font = GLUT_BITMAP_8_BY_13);
                   
void gltEndRasterText();

void gltBSpline3d(GPoint3d **ctrGrid, int nx, int nz);

#endif
