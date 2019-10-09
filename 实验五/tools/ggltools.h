#ifndef GLTOOLS_H
#define GLTOOLS_H

#include <gl/glut.h>

void gltBeginRasterText(int w, int h);

void gltRasterText(double x, double y, const char *text, 
                   void *font = GLUT_BITMAP_8_BY_13);
                   
void gltEndRasterText();

void gltWireCube(double len);

void gltWireCone(double r, double h, int slices, int stacks);

void gltWireSphere(double r, int slices, int stacks);

#endif
