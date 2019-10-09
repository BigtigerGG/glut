/*******************************************************************************
 * 图形学教学程序：多边形逐边裁剪算法
 * 版权声明：您可以随意使用、复制或传播本代码，但请保留原作者姓名
 * 作者：成都理工大学信息工程学院-邓飞  2010.8
*******************************************************************************/
 
#include <gl/glut.h>
#include <stdio.h>
#include "tools.h"
#include "gpoint2.h"
#include "gpolygon2.h"

// 裁剪窗口矩形
GRect2d gWinRect;

// 多边形顶点数组 
GPolygon2d gPoly;

// 裁剪多边形顶点数组 
GPolygon2d gCPoly;

// 鼠标左键选中的控制点 
int gSelectedIndex = -1;

// Shift键是否按下
bool gIsShiftDown = false; 

void drawPoints(const GPolygon2d &points)
{
    for(int i=0; i<points.count(); i++)
    {
        // 绘制矩形控制点
        glColor3f(0, 0, 1); 
        gltRect2d(points[i].x()-5, points[i].y()-5,
                  points[i].x()+5, points[i].y()+5);
    }
}

void drawTags()
{
    char text[32];
    for(int i=0; i<gPoly.count(); i++)
    {
        // 标注坐标 
        sprintf(text, "(%d, %d)", (int)gPoly[i].x(), (int)gPoly[i].y());
        glColor3f(1, 0, 0);
        gltRasterText(gPoly[i].x()+10, gPoly[i].y()-5, text);
    }
}

// 绘制事件函数 
void displayEvent()
{
    int i, n;
    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glColor3f(0, 0, 1);
    gltRect2d(gWinRect.x0(), gWinRect.y0(), gWinRect.x1(), gWinRect.y1());
    
    drawPoints(gPoly);
    
    glColor3f(0, 0, 0);
    n = gPoly.count();
    for(i=0; i<n; i++)
    {
        gltLine2d(gPoly[i].x(), gPoly[i].y(),
            gPoly[(i+1)%n].x(), gPoly[(i+1)%n].y());
    }
    
    glColor3f(1, 0, 0);
    glLineWidth(2);
    n = gCPoly.count();
    for(i=0; i<n; i++)
    {
        gltLine2d(gCPoly[i].x(), gCPoly[i].y(),
            gCPoly[(i+1)%n].x(), gCPoly[(i+1)%n].y());
    }
    glLineWidth(1);

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

// 鼠标移动事件函数 
void mouseMoveEvent(int x, int y)
{
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    y = h - y;
    if(gSelectedIndex >= 0)
    {
        gPoly[gSelectedIndex].set(x, y);
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
            int index = gPoly.findByCoord(x, y);
            if(index < 0)   // 添加控制点
            {
                index = gPoly.count(); 
                gPoly.addLast(GPoint2d(x, y));
                gSelectedIndex = index;
            }
            else            // 修改(删除)已有控制点 
            {
                if(glutGetModifiers() & GLUT_ACTIVE_SHIFT) // 删除
                {
                    gPoly.remove(index);
                }
                else
                {
                    gSelectedIndex = index;
                }
            }
        }
        else if(state == GLUT_UP)
        {    
            if(gSelectedIndex >= 0)
            {
                gPoly[gSelectedIndex].set(x, y);
                glutPostRedisplay();
                gSelectedIndex = -1;
            }
        }            
        glutPostRedisplay();
    }
    else if(button == GLUT_RIGHT_BUTTON)
    {
        gltPolyClip2d(gPoly, gCPoly, gWinRect);
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
	glutCreateWindow("Polygon Clip");
	glInit();
	
	glutReshapeFunc(resizeEvent);
	glutDisplayFunc(displayEvent);
	
	glutMouseFunc(mouseEvent);
	glutMotionFunc(mouseMoveEvent);
	
	glutMainLoop();
	
	return 0;
}
