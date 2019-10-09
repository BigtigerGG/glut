#include <gl/glut.h>

int gx = 50;
int gy = 100;


void onDisplay()
{
	// 设置清屏颜色
	glClearColor(1,1,1,0);
	// 用指定颜色清楚
	glClear(GL_COLOR_BUFFER_BIT);
	
	static char text[] = "Hello world!";
	// 定位输出位置
	glRasterPos2d(gx, gy);
	// 设置字符串颜色
	glColor3f(1,0,0);
	for (int i = 0; text[i] != '\0'; i++)
	{
		// 输出字符
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text[i]);
	}
	// 交换双缓存
	glutSwapBuffers();
}

void onReshape(int w, int h)
{
	// 设置视口大小
	glViewport(0, 0, w, h);
	// 切换矩阵模式为投影矩阵
	glMatrixMode(GL_PROJECTION);
	// 载入单位矩阵
	glLoadIdentity();
	// 进行二维平行投影
	gluOrtho2D(0, w, h, 0);
	// 切换矩阵模式为模型矩阵
	glMatrixMode(GL_MODELVIEW);
	// 发送重绘
	glutPostRedisplay();
}

void onMouse(int button, int state, int x, int y)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		gx = x;
		gy = y;
		glutPostRedisplay();
	}
}

int main(int argc, char *argv[])
{
	// 初始换glut
	glutInit(&argc, argv);
	// 设置OpenGL显示模式
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	// 设置窗口初始尺寸
	glutInitWindowSize(400, 300);
	// 设置窗口初始位置
	glutInitWindowPosition(100, 100);
	// 设置窗口标题
	glutCreateWindow("Hello");
	// 设置显示回调函数
	glutDisplayFunc(onDisplay);
	// 设置窗口尺寸变化回调函数
	glutReshapeFunc(onReshape);
	// 设置鼠标事件回调函数
	glutMouseFunc(onMouse);
	// 进入 glut 事件循环
	glutMainLoop();
	return 0;
}
