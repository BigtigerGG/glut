#include <string.h>
#include "tools.h"

template <class T>
void swap(T &a, T &b)
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

char clipCode(const GPoint2d &pt, const GRect2d &rc)
{
	char code = 0;

	if(pt.y() > rc.y1()) code |= 0x01;
	else if(pt.y() < rc.y0()) code |= 0x02;

	if(pt.x() > rc.x1()) code |= 0x04;
	else if(pt.x() < rc.x0()) code |= 0x08;

	return code;
}

bool gltLineClip2d(GPoint2d &pt0, GPoint2d &pt1, const GRect2d &rc)
{
	return false;
}
