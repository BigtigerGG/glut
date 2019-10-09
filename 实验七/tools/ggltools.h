#ifndef GLTOOLS_H
#define GLTOOLS_H

#include <gl/glut.h>
#include <stdio.h>

void gltBeginRasterText(int w, int h);

void gltRasterText(double x, double y, const char *text, 
                   void *font = GLUT_BITMAP_8_BY_13);
                   
void gltEndRasterText();

// ��������
// fRadius:	�뾶
// iSlices:	��Ƭ��Ŀ
// iStacks: Z�����з���Ŀ
void gltDrawSphere(double fRadius, int iSlices, int iStacks);

#endif
