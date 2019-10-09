/*******************************************************************************
 * 图形学教学程序：交互式直线绘制
 * 版权声明：您可以随意使用、复制或传播本代码，但请保留原作者姓名
 * 作者：成都理工大学信息工程学院-邓飞  2006.3
*******************************************************************************/
 
#include <gl/glut.h>
#include <stdio.h>
#include "ggltools.h"
#include "gpoint2.h"
#include "gline.h"

// 直线对象 
GLine2i gLine;

// 是否需要绘制 
bool gIsPaint = false;

// 鼠标左键是否按下 
bool gIsLBtnDown = false;

// 绘制事件函数 
void onDisplay()
{
    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    if(gIsPaint)
	{
		GPoint2i pt0, pt1;
		pt0 = gLine.getBeginPt();
		pt1 = gLine.getEndPt();
		
		// 绘制直线
		glColor3f(0,0,0);
		gltLine2i(pt0.x(), pt0.y(), pt1.x(), pt1.y());
		// 绘制七点红色十字
		glColor3f(1,0,0);
		gltLine2i(pt0.x()-8, pt0.y(), pt0.x()+8, pt0.y());
		gltLine2i(pt0.x(), pt0.y()-8, pt0.x(), pt0.y()+8);
		// 绘制尾点方框
		glColor3f(0, 0, 1);
		gltRect2i(pt1.x()-5, pt1.y()-5, pt1.x()+5, pt1.y()+5);
		// 标注坐标
		char text[32];
		sprintf(text, "(%d, %d)", pt0.x(), pt0.y());
		glColor3f(1, 0, 0);
		gltRasterText(pt0.x()+10, pt0.y()-5, text);
		sprintf(text, "(%d, %d)", pt1.x(), pt1.y());
		glColor3f(0, 0, 1);
		gltRasterText(pt1.x()+10, pt1.y()-5, text);
	}
    glutSwapBuffers();  // 交换缓存 
}

// 窗体尺寸变化事件 
void onReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluOrtho2D(0, w, h, 0);
    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();
}       

void onMouseMotion(int x, int y)
{
    if (gIsLBtnDown)
	{
		gLine.setEndPt(GPoint2i(x,y));
		glutPostRedisplay();
	}
}        

// 鼠标事件函数 
void onMouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			gLine.set(x,y,x,y);
			gIsLBtnDown = true;
			gIsPaint = true;
		}
		else if(state == GLUT_UP)
		{
			gLine.setEndPt(GPoint2i(x,y));
			gIsLBtnDown = false;
		}
	}
	
	glutPostRedisplay();
}                   

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(400, 300);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Line 2D");
	
	glutReshapeFunc(onReshape);
	glutDisplayFunc(onDisplay);
	glutMouseFunc(onMouse);
	glutMotionFunc(onMouseMotion);
	
	glutMainLoop();
	
	return 0;
}
