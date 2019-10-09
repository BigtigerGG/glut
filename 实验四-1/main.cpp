/*******************************************************************************
 * 图形学教学程序：编码裁剪
 * 版权声明：您可以随意使用、复制或传播本代码，但请保留原作者姓名
 * 作者：成都理工大学信息工程学院-邓飞  2010.8
*******************************************************************************/
 
#include <gl/glut.h>
#include <stdio.h>
#include "tools.h"
#include "gpoint2.h"
#include "grect2.h"

// 记录直线的两个端点 
GPoint2d gPt0, gPt1;

// 裁减以后的端点 
GPoint2d gCPt0, gCPt1;

// 裁剪窗口矩形
GRect2d gWinRect;

// 是否需要绘制 
bool gIsPaint = false;

// 鼠标左键是否按下 
bool gIsLBtnDown = false;

// 绘制事件函数 
void displayEvent()
{
    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glColor3f(0, 0, 1);
	gltRect2d(gWinRect.x0(), gWinRect.y0(), gWinRect.x1(), gWinRect.y1());
    
    if(gIsPaint)
    {
        // 绘制直线 
        glColor3f(0, 0, 0);
        gltLine2d(gPt0.x(), gPt0.y(), gPt1.x(), gPt1.y());
        
        // 绘制起点红色十字 
        glColor3f(1, 0, 0);
        gltLine2d(gPt0.x()-8, gPt0.y(), gPt0.x()+8, gPt0.y());
        gltLine2d(gPt0.x(), gPt0.y()-8, gPt0.x(), gPt0.y()+8);
        
        // 绘制尾点方框 
        glColor3f(0, 0, 1);
        gltRect2d(gPt1.x()-5, gPt1.y()-5, gPt1.x()+5, gPt1.y()+5);
        
        if(!gIsLBtnDown)
        {
            glColor3f(1, 0, 0);
            glLineWidth(2);
            gltLine2d(gCPt0.x(), gCPt0.y(), gCPt1.x(), gCPt1.y());
            glLineWidth(1);
        }
        
        // 标注坐标 
        char text[32];
        sprintf(text, "(%d, %d)", (int)gPt0.x(), (int)gPt0.y());
        glColor3f(1, 0, 0);
        gltRasterText(gPt0.x()+10, gPt0.y()-5, text);
        
        sprintf(text, "(%d, %d)", (int)gPt1.x(), (int)gPt1.y());
        glColor3f(0, 0, 1);
        gltRasterText(gPt1.x()+10, gPt1.y()-5, text);
    }

    glFlush();
    glutSwapBuffers();  // 交换缓存 
}

// 窗体尺寸变化事件 
void resizeEvent(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluOrtho2D(0, w, 0, h);
    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();
}       

void mouseMoveEvent(int x, int y)
{
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    y = h - y;
    if(gIsLBtnDown)
    {
        gPt1.set(x, y);
        glutPostRedisplay();
    }
}        

// 鼠标事件函数 
void mouseEvent(int button, int state, int x, int y)
{
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    y = h - y;
    if(button == GLUT_LEFT_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            gPt0.set(x, y);
            gPt1 = gPt0;
            gIsLBtnDown = true;
            gIsPaint = true;
        }
        else if(state == GLUT_UP)
        {    
            gPt1.set(x, y);
            
            gCPt0 = gPt0;       gCPt1 = gPt1;
            if(!gltLineClip2d(gCPt0, gCPt1, gWinRect))
            {
                gCPt0.set(-1, -1);
                gCPt1.set(-1, -1);
            }
            gIsLBtnDown = false;
        }            
        glutPostRedisplay();
    }
}                   

// openGL初始化函数 
void glInit()
{
	gWinRect.set(50, 60, 350, 260);
} 

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 300);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Code Clip");
	glInit();
	
	glutReshapeFunc(resizeEvent);
	glutDisplayFunc(displayEvent);
	
	glutMouseFunc(mouseEvent);
	glutMotionFunc(mouseMoveEvent);
	
	glutMainLoop();
	
	return 0;
}
