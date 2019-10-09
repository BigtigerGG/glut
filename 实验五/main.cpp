/*******************************************************************************
 * 图形学教学程序：基本三维图形绘制
 * 版权声明：您可以随意使用、复制或传播本代码，但请保留原作者姓名
 * 作者：成都理工大学信息工程学院-邓飞  2006.3
*******************************************************************************/
#include <gl/glut.h>
#include <stdio.h>
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

// 绘制事件函数 
void onDisplay()
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glPushMatrix();
        //glTranslatef(0, 0, -1.5f);
        drawPlane();
        
        glLineWidth(2);
        
        glPushMatrix();
            glTranslatef(-0.3, 0, -0.3);
            glColor3f(1, 0, 0);
            glutWireCube(0.4f);
        glPopMatrix();
        
        glPushMatrix();
            glTranslatef(0.3, 0, -0.3);
            glColor3f(0, 1, 0);
            glutWireSphere(0.2f, 16, 16);
        glPopMatrix();
        
        glPushMatrix();
            glTranslatef(0, 0, 0.3);
            glRotatef(-90, 1, 0, 0);
            glColor3f(1, 1, 0);
            glutWireCone(0.2f, 0.6f, 16, 8);
        glPopMatrix();
        
    glPopMatrix();
    
    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    glColor3f(1, 1, 1);
    gltBeginRasterText(w, h);
    //gltRasterText(10, 20, "Basic OpenGL Ortho Program");
    gltEndRasterText();

    glFlush();
    glutSwapBuffers();  // 交换缓存 
}

// 窗体尺寸变化事件 
void onReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();
}       

// openGL初始化函数 
void glInit()
{
} 

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 300);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Basic 3D");
	glInit();
	
	glutReshapeFunc(onReshape);
	glutDisplayFunc(onDisplay);
	
	glutMainLoop();
	
	return 0;
}
