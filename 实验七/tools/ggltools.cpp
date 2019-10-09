#include <math.h>
#include "ggltools.h"
#include "gmath.h"

void gltBeginRasterText(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, w, h, 0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
}

void gltEndRasterText()
{
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
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

// 绘制球体
// fRadius:	半径
// nslice:	切片数目
// nstack:  Z方向切分数目
void gltDrawSphere(double radius, int nslice, int nstack)
{
	// Z方向角度间隔
	double drho = PI / nstack;
	// XOY面上角度间隔
	double dtheta = 2.0 * PI / nslice;
	double ds = 1.0 / nslice;
	double dt = 1.0 / nstack;
	double t = 1.0;	
	double s = 0.0;
	GLint i, j;
	
	for(i=0; i<nstack; i++) 
	{
		double rho = i * drho;
		double srho = sin(rho);
		double crho = cos(rho);
		double srho1 = sin(rho + drho);
		double crho1 = cos(rho + drho);
		
		// 三角带绘制方式为
		// v0---v2---v4
		// |  / |  / |
		// v1---v3---v5
		glBegin(GL_TRIANGLE_STRIP);
		s = 0.0f;
		for(j=0; j<=nslice; j++)
		{
			double theta = j%nslice * dtheta;
			double stheta = sin(theta);
			double ctheta = cos(theta);
			double x, y, z;
			
			x = stheta * srho;
			y = crho;
			z = ctheta * srho;
			glTexCoord2d(s, t);
			glNormal3d(x, y, z);
			glVertex3d(x * radius, y * radius, z * radius);

			x = stheta * srho1;
			y = crho1;
			z = ctheta * srho1;
			glTexCoord2d(s, t - dt);
			glNormal3d(x, y, z);
			glVertex3d(x * radius, y * radius, z * radius);
			
			s += ds;
		}
		glEnd();
		t -= dt;
	}
}