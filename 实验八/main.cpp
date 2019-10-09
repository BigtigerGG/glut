/*******************************************************************************
 * ͼ��ѧ��ѧ���򣺼����׷����3D��ת 
 * ��Ȩ����������������ʹ�á����ƻ򴫲������룬���뱣��ԭ��������
 * ���ߣ��ɶ�����ѧ��Ϣ����ѧԺ-�˷�  2006.3
*******************************************************************************/
#include <gl/glut.h>
#include <stdio.h>
#include "gvector3d.h"
#include "gmatrix3d.h"
#include "ggltools.h"
#include "glight.h"
#include "gmaterial.h"

// ���λ�� 
int gMouseX = -1;
int gMouseY = -1;

// �Ƿ�������׷���� 
bool gIsStartTrackBall = false;

// ��ת���� 
GMatrix3d gRotMatrix;

// ��Դ
GLight gLight0;

// ������ά��ӳ��Ϊ��������(�������׷����) 
GVector3d mousePtToSphereVec(int x, int y, int w, int h)
{
    GVector3d vec;
    vec.setX((2.0*x - w) / w);
    vec.setY((h - 2.0*y) / h);
    double r = (vec.x()*vec.x()+vec.y()*vec.y());
    if(r > 1) r = 1;
    vec.setZ(sqrt(1 - r));
    vec.normalize();
    return vec;
}

// �����¼����� 
void onDisplay()
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0, 0, -3.5f);
    glMultMatrixd(gRotMatrix);
    
	glDisable(GL_LIGHTING);
    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    glColor3f(1, 1, 1);
    gltBeginRasterText(w, h);
    gltRasterText(10, 20, "Drag the left button to rotate the scene");
    gltEndRasterText();
    
    glutSwapBuffers();  // �������� 
}

// ����ߴ�仯�¼� 
void onReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    h = h > 0 ? h : 1;
    
    float aspect = (float)w / h;
    if(aspect > 1)
    {
        glOrtho(-1.5*aspect, 1.5*aspect, -1.5, 1.5, 0, 10);
    }
    else
    {
        glOrtho(-1.5, 1.5, -1.5/aspect, 1.5/aspect, 0, 10);
    }   
    
    glutPostRedisplay();
}       

void onMouseMove(int x, int y)
{
    if(gIsStartTrackBall)
    {
        if(x != gMouseX || y != gMouseY)
        {
            int w = glutGet(GLUT_WINDOW_WIDTH);
            int h = glutGet(GLUT_WINDOW_HEIGHT);
            GVector3d lastVec = mousePtToSphereVec(gMouseX, gMouseY, w, h);
            GVector3d currentVec = mousePtToSphereVec(x, y, w, h);
            double rotAngle = acos(lastVec.dotMult(currentVec))*RADIAN_TO_ANGLE;
            GVector3d axis = lastVec.crossMult(currentVec);
			if (axis.getLength() <= 0) return ;
            axis.normalize();

            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            glLoadIdentity();
            glRotated(rotAngle, axis[0], axis[1], axis[2]);
            glMultMatrixd(gRotMatrix);
            glGetDoublev(GL_MODELVIEW_MATRIX, gRotMatrix);
            
            glPopMatrix();
			gMouseX = x;        gMouseY = y;
            glutPostRedisplay();
        }
    }
}        

// ����¼����� 
void onMouse(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            gMouseX = x;
            gMouseY = y;
            gIsStartTrackBall = true;
        }
        else if(state == GLUT_UP)
        {    
            gIsStartTrackBall = false;
        }            
        glutPostRedisplay();
    }
}       

// openGL��ʼ������ 
void glInit()
{
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	
	gLight0.init(0, gDirLight);
	gLight0.setPosition(0, 4, -4);
	gLight0.turnOn();
} 

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 300);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("B-Spline 3D");
	glInit();
	
	glutReshapeFunc(onReshape);
	glutDisplayFunc(onDisplay);
	
	glutMouseFunc(onMouse);
	glutMotionFunc(onMouseMove);
	
	glutMainLoop();
	
	return 0;
}
