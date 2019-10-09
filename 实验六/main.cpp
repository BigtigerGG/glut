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

void drawPlane()
{
    glColor3f(0.6f, 0.6f, 0.6f);
    for(float u=-1; u<1.01; u+=0.2f)
    {
        glBegin(GL_LINES);
        glVertex3f(-1, 0, u);
        glVertex3f(1, 0, u);
        
        glVertex3f(u, 0, -1);
        glVertex3f(u, 0, 1);
        glEnd();
    }
}

// �����¼����� 
void onDisplay()
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0, 0, -3.5f);
    
    glLineWidth(1);
    drawPlane();
    
    glLineWidth(3);
    
    glPushMatrix();
        glTranslatef(-0.3, 0.2, -0.3);
        glColor3f(1, 0, 0);
        glutWireCube(0.4f);
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(0.3, 0.2, -0.3);
        glColor3f(0, 1, 0);
        glutWireSphere(0.2f, 16, 16);
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(0, 0, 0.3);
        glRotatef(-90, 1, 0, 0);
        glColor3f(1, 1, 0);
        glutWireCone(0.2f, 0.6f, 16, 8);
    glPopMatrix();
    
    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    glColor3f(1, 1, 1);
    gltBeginRasterText(w, h);
    gltRasterText(10, 20, "Drag the left button to rotate the scene");
    gltEndRasterText();
    
    glFlush();
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
	gluPerspective(40, aspect, 0.5, 10);
    
    glutPostRedisplay();
}       

void onMouseMove(int x, int y)
{
}        

// ����¼����� 
void onMouse(int button, int state, int x, int y)
{
}       

// openGL��ʼ������ 
void glInit()
{
} 

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 300);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Virtual Track Ball");
	glInit();
	
	glutReshapeFunc(onReshape);
	glutDisplayFunc(onDisplay);
	
	glutMouseFunc(onMouse);
	glutMotionFunc(onMouseMove);
	
	glutMainLoop();
	
	return 0;
}
