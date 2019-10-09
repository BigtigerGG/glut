#ifndef GLTOOLS_H
#define GLTOOLS_H

#include <gl/glut.h>
#include <stdio.h>

void gltBeginRasterText(int w, int h);

void gltRasterText(double x, double y, const char *text, 
                   void *font = GLUT_BITMAP_8_BY_13);
                   
void gltEndRasterText();

// 绘制球体
// fRadius:	半径
// iSlices:	切片数目
// iStacks: Z方向切分数目
void gltDrawSphere(double fRadius, int iSlices, int iStacks);

#endif
