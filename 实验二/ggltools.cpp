#include <math.h>
#include "ggltools.h"

template <class T>
void swap(T &a, T &b)
{
	T tmp = a;
	a = b;
	b = tmp;
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

inline int gRound(float x)
{
	return x >= 0 ? (int)(x+0.5f) : (int)(x-0.5f);
}

void gltLine2i(int x0, int y0, int x1, int y1)
{
	/*bool isSwapXY = false;
	int x, y, tx;
	float k, yf;

	if(abs(x1-x0) < abs(y1-y0))
	{
		swap(x0, y0);
		swap(x1, y1);
		isSwapXY = true;
	}
	if(x1 == x0) return ;
	if(x0 <= x1) tx = 1;
	else tx = -1;
	k = (float)(y1-y0) / (x1-x0) * tx;
	x = x0;		yf = y0;
	while(x != x1)
	{
		y = gRound(yf);
		glBegin(GL_POINTS);
		if(isSwapXY) glVertex2i(y, x);
		else glVertex2i(x, y);
		glEnd();
		x += tx;
		yf += k;
	}*/

	bool isSwapXY = false;
	int x, y, dx, dy, tx, ty, e, dx2, dy2;

	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	if(dx < dy)
	{
		swap(x0, y0);
		swap(x1, y1);
		swap(dx, dy);
		isSwapXY = true;
	}

	if(x0 <= x1) tx = 1;
	else tx = -1;
	if(y0 <= y1) ty = 1;
	else ty = -1;

	e = -dx;
	x = x0;		y = y0;
	dx2 = dx << 1;
	dy2 = dy << 1;

	glBegin(GL_POINTS);
	while(x != x1)
	{
		if(isSwapXY) glVertex2i(y, x);
		else glVertex2i(x, y);
		
		x += tx;
		e += dy2;
		if(e > 0)
		{
			y += ty;
			e -= dx2;
		}
	}

	if(isSwapXY) glVertex2i(y, x);
	else glVertex2i(x, y);
	glEnd();

	/*bool isSwapXY = false;
	int x, y, dx, dy, tx, ty, a, b, di;
	
	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	
	if(dx < dy)
	{
		isSwapXY = true;
		swap(x0, y0);
		swap(x1, y1);
		swap(dx, dy);
	}
	if(y1 < y0) ty = -1;
	else ty = 1;
	if(x1 < x0) tx = -1;
	else tx = 1;

	a = -dy;
	b = dx;
	x = x0;		y = y0;
	di = 2*a + b;
	while(x != x1)
	{
		glBegin(GL_POINTS);
			if(isSwapXY) glVertex2i(y, x);
			else glVertex2i(x, y);
		glEnd();

		x += tx;
		if(di >= 0)
		{
			di += 2*a;
		}
		else
		{
			di += 2*(a+b);
			y += ty;
		}
	}*/
}

void gltRect2i(int x0, int y0, int x1, int y1)
{
	gltLine2i(x0, y0, x1, y0);
	gltLine2i(x1, y0, x1, y1);
	gltLine2i(x1, y1, x0, y1);
	gltLine2i(x0, y1, x0, y0);
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
    glBegin(GL_LINE_STRIP);
        glVertex2d(x0, y0);
        glVertex2d(x1, y0);
        
        glVertex2d(x1, y1);
        
        glVertex2d(x0, y1);
        
        glVertex2d(x0, y0);
    glEnd();
}
