#include <string.h>
#include <math.h>
#include "tools.h"

template <class T>
void gSwap(T &a, T &b)
{
	T t = a;
	a = b;
	b = t;
}

int gltRound(double x)
{
	return x > 0 ? (int)(x+0.5) : (int)(x-0.5);
}

int gltTrunc(double x)
{
	return (int)x;
}

void gltRasterText(double x, double y, const char *text, void *font)
{
    if(text == NULL) return ;
    
    glRasterPos2d(x, y);
    for(int i=0; text[i] != '\0'; i++)
    {
        glutBitmapCharacter(font, text[i]);
    } 
}

void gltLine2i(int x0, int y0, int x1, int y1)
{
    glBegin(GL_LINES);
	glVertex2i(x0, y0);
	glVertex2i(x1, y1);
    glEnd();
}

void gltRect2i(int x0, int y0, int x1, int y1)
{
    glBegin(GL_LINES);
	glVertex2i(x0, y0);
	glVertex2i(x1, y0);
	
	glVertex2i(x1, y0);
	glVertex2i(x1, y1);
	
	glVertex2i(x1, y1);
	glVertex2i(x0, y1);
	
	glVertex2i(x0, y1);
	glVertex2i(x0, y0);
    glEnd();
}

void gltLine2d(double x0, double y0, double x1, double y1)
{
    glBegin(GL_LINES);
        glVertex2d(x0, y0);
        glVertex2d(x1, y1);
    glEnd();
}

void gltRect2d(double x0, double y0, double x1, double y1)
{
    glBegin(GL_LINES);
        glVertex2d(x0, y0);
        glVertex2d(x1, y0);
        
        glVertex2d(x1, y0);
        glVertex2d(x1, y1);
        
        glVertex2d(x1, y1);
        glVertex2d(x0, y1);
        
        glVertex2d(x0, y1);
        glVertex2d(x0, y0);
    glEnd();
}

void winEdgeClip2d(int edge, double v, const GPolygon2d &src, GPolygon2d &dst)
{
	
}

void gltPolyClip2d(const GPolygon2d &src, GPolygon2d &dst, const GRect2d &rc)
{
	
}