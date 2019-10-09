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

// ���λ�� 
int gMouseX = -1;
int gMouseY = -1;

// �Ƿ�������׷���� 
bool gIsStartTrackBall = false;

// ��ת���� 
GMatrix3d gRotMatrix;

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
    glMultMatrixd(gRotMatrix);

	glDisable(GL_LIGHTING);
	glLineWidth(1);
	drawPlane();

	glPushMatrix();
	glTranslatef(0.3, 0.2, -0.3);
	glColor3f(0, 1, 0);
	glutWireSphere(0.2f, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.3, 0.2, -0.3);
	glColor3f(1, 0, 0);
	glutWireCube(0.4f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 0.3);
	glRotatef(-90, 1, 0, 0);
	glColor3f(1, 1, 0);
	glutWireCone(0.2f, 0.6f, 16, 8);
	glPopMatrix();
    
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
	gluPerspective(45, aspect, 1.5, 10); 
    
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
			
			GMatrix3d m = GMatrix3d::createRotate(rotAngle, axis);
			gRotMatrix *= m;
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
} 

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(400, 300);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Earth");

	glInit();
	
	glutReshapeFunc(onReshape);
	glutDisplayFunc(onDisplay);
	
	glutMouseFunc(onMouse);
	glutMotionFunc(onMouseMove);
	
	glutMainLoop();
	
	return 0;
}
