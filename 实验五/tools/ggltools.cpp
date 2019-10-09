#include "ggltools.h"
#include <math.h>
#include <stdio.h>
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

void gltWireCube(double len)
{
    double pts[8][3];
    pts[0][0] = -len/2; pts[0][1] = -len/2; pts[0][2] = len/2;
    pts[1][0] = len/2; pts[1][1] = -len/2; pts[1][2] = len/2;
    pts[2][0] = len/2; pts[2][1] = -len/2; pts[2][2] = -len/2;
    pts[3][0] = -len/2; pts[3][1] = -len/2; pts[3][2] = -len/2;
    
    pts[4][0] = -len/2; pts[4][1] = len/2; pts[4][2] = len/2;
    pts[5][0] = len/2; pts[5][1] = len/2; pts[5][2] = len/2;
    pts[6][0] = len/2; pts[6][1] = len/2; pts[6][2] = -len/2;
    pts[7][0] = -len/2; pts[7][1] = len/2; pts[7][2] = -len/2;
    
    int i;
    
    for(i=0; i<4; i++)
    {
        glBegin(GL_LINES);
            glVertex3dv(pts[i]);
            glVertex3dv(pts[(i+1)%4]);
        glEnd();
    }
    
    for(i=0; i<4; i++)
    {
        glBegin(GL_LINES);
            glVertex3dv(pts[i+4]);
            glVertex3dv(pts[(i+1)%4+4]);
        glEnd();
    }
    
    for(i=0; i<4; i++)
    {
        glBegin(GL_LINES);
            glVertex3dv(pts[i]);
            glVertex3dv(pts[i+4]);
        glEnd();
    }
}

void gltWireCone(double r, double h, int slices, int stacks)
{
    int i, j;
    double af, daf, s;
    daf = 2*PI/slices;
    
    double x0, z0, x1, z1;
    x0 = r;     z0 = 0;
    af = daf;
    for(i=0; i<slices; i++)
    {
        x1 = r*cos(af);
        z1 = r*sin(af);
        glBegin(GL_LINES);
            glVertex3d(x0, 0, z0);
            glVertex3d(x1, 0, z1);
            
            glVertex3d(x1, 0, z1);
            glVertex3d(0, 0, 0);
            
            glVertex3d(x1, 0, z1);
            glVertex3d(0, h, 0);
        glEnd();
        
        for(j=0; j<stacks; j++)
        {
            s = (double)(stacks - j) / stacks;
            glBegin(GL_LINES);
                glVertex3d(x0*s, (1-s)*h, z0*s);
                glVertex3d(x1*s, (1-s)*h, z1*s);
            glEnd();
        }
        
        x0 = x1;    z0 = z1;
        af += daf;
    }
}

void gltWireSphere(double r, int slices, int stacks)
{
    int i, j;
    double af, daf, bt, dbt;
    double x0, y0, z0, x1, y1, z1;
    
    daf = 2*PI/stacks;
    dbt = 2*PI/slices;
    
    af = 0;   bt = 0;
    for(i=0; i<slices/2; i++)
    {
        x0 = r*cos(af)*cos(bt);
        y0 = r*sin(af);
        z0 = r*cos(af)*sin(bt);
        for(j=0; j<stacks; j++)
        {
            af += daf;
            x1 = r*cos(af)*cos(bt);
            y1 = r*sin(af);
            z1 = r*cos(af)*sin(bt);
            
            glBegin(GL_LINES);
                glVertex3d(x0, y0, z0);
                glVertex3d(x1, y1, z1);
            glEnd();
            
            x0 = x1;    y0 = y1;    z0 = z1;
        }
        bt += dbt;
    }
    
    af = daf;   bt = 0;
    for(i=1; i<stacks-1; i++)
    {
        x0 = r*cos(af)*cos(bt);
        y0 = r*sin(af);
        z0 = 0;
        for(j=0; j<slices; j++)
        {
            bt += daf;
            x1 = r*cos(af)*cos(bt);
            y1 = r*sin(af);
            z1 = r*cos(af)*sin(bt);
            
            glBegin(GL_LINES);
                glVertex3d(x0, y0, z0);
                glVertex3d(x1, y1, z1);
            glEnd();
            
            x0 = x1;    y0 = y1;    z0 = z1;
        }
        af += daf;
    }
}
    
