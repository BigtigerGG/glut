#include <gl/glut.h>

int gx = 50;
int gy = 100;


void onDisplay()
{
	// ����������ɫ
	glClearColor(1,1,1,0);
	// ��ָ����ɫ���
	glClear(GL_COLOR_BUFFER_BIT);
	
	static char text[] = "Hello world!";
	// ��λ���λ��
	glRasterPos2d(gx, gy);
	// �����ַ�����ɫ
	glColor3f(1,0,0);
	for (int i = 0; text[i] != '\0'; i++)
	{
		// ����ַ�
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text[i]);
	}
	// ����˫����
	glutSwapBuffers();
}

void onReshape(int w, int h)
{
	// �����ӿڴ�С
	glViewport(0, 0, w, h);
	// �л�����ģʽΪͶӰ����
	glMatrixMode(GL_PROJECTION);
	// ���뵥λ����
	glLoadIdentity();
	// ���ж�άƽ��ͶӰ
	gluOrtho2D(0, w, h, 0);
	// �л�����ģʽΪģ�;���
	glMatrixMode(GL_MODELVIEW);
	// �����ػ�
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
	// ��ʼ��glut
	glutInit(&argc, argv);
	// ����OpenGL��ʾģʽ
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	// ���ô��ڳ�ʼ�ߴ�
	glutInitWindowSize(400, 300);
	// ���ô��ڳ�ʼλ��
	glutInitWindowPosition(100, 100);
	// ���ô��ڱ���
	glutCreateWindow("Hello");
	// ������ʾ�ص�����
	glutDisplayFunc(onDisplay);
	// ���ô��ڳߴ�仯�ص�����
	glutReshapeFunc(onReshape);
	// ��������¼��ص�����
	glutMouseFunc(onMouse);
	// ���� glut �¼�ѭ��
	glutMainLoop();
	return 0;
}
