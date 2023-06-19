#include <gl/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "math.h"

int defSCREEN_WIDTH = 600, defSCREEN_HEIGHT = 600;
int g_lineNum;
bool g_startSelect, g_endSelect, g_finish;
wcPt2D* g_lines;

void Display();
void Reshape(int w, int h);
void Keyboard(unsigned char uchKey, int iXPos, int iYPos);
void PassiveMotionFunc(int iXPos, int iYPos);
void MyInit(void);
void SetPixel(int x, int y);
void BresLine(int x0, int y0, int x1, int y1, void (*SetPixel)(int x, int y));
void MidPLine(int x0, int y0, int x1, int y1, void (*SetPixel)(int x, int y));
void MidPointCircle(int x0, int y0, int x1, int y1, void (*SetPixel)(int x, int y));
void MidPointEllipse(int x0, int y0, int x1, int y1, void (*SetPixel)(int x, int y));
void Cirplot(int x0, int y0, int x, int y, void (*SetPixel)(int x, int y));
void lineSegment(int x0, int y0, int x1, int y1);
void EllipsePoints(int x0, int y0, int x, int y, void (*SetPixel)(int x, int y));
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	MyInit();
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(defSCREEN_WIDTH, defSCREEN_HEIGHT);

	int windowHandle = glutCreateWindow("Glut Lines, Circle, and Ellipse");
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Display);
	glutKeyboardFunc(Keyboard);
	glutPassiveMotionFunc(PassiveMotionFunc);

	glutMainLoop();
	if (g_lines) free(g_lines);
	return 0;

}

void SetPixel(int x, int y)
{
	glEnable(GL_POINT_SMOOTH);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}
void Display()  //����ʧЧ��Ļص�����
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_LINE_SMOOTH);
	//glLineWidth(5.0);//�����߿���
	glPointSize(1.0);//���õ����
	glColor3f(0, 0, 1.0);//���õ���ɫ����
	for (int i = 0; i < g_lineNum; i++)
	{
		//MidPLine(ROUND(g_lines[i * 2].x), ROUND(g_lines[i * 2].y), ROUND(g_lines[i * 2 + 1].x),ROUND(g_lines[i * 2 + 1].y), SetPixel); // �е㻭���㷨
		//BresLine(ROUND(g_lines[i * 2].x), ROUND(g_lines[i * 2].y), ROUND(g_lines[i * 2 + 1].x), ROUND(g_lines[i * 2 + 1].y), SetPixel); // Bresenham�㷨
		//MidPointCircle(ROUND(g_lines[i * 2].x), ROUND(g_lines[i * 2].y), ROUND(g_lines[i * 2 + 1].x),ROUND(g_lines[i * 2 + 1].y), SetPixel); // �е㻭Բ�㷨
		//MidPointEllipse(ROUND(g_lines[i * 2].x), ROUND(g_lines[i * 2].y), ROUND(g_lines[i * 2 + 1].x),ROUND(g_lines[i * 2 + 1].y), SetPixel); // �е㻭��Բ�㷨
		//lineSegment(ROUND(g_lines[i * 2].x), ROUND(g_lines[i * 2].y), ROUND(g_lines[i * 2 + 1].x), ROUND(g_lines[i * 2 + 1].y)); // ��OpenGL��ֱ�߷�����ɻ���
	}
	glFlush();

}
void Keyboard(unsigned char uchKey, int iXPos, int iYPos)  // ���̻ص�����
{
	if (iXPos < 0 || iXPos >= defSCREEN_WIDTH || iYPos < 0 || iYPos >= defSCREEN_HEIGHT)
		return;

	if (uchKey == 27/*Esc*/) {
		exit(0);
	}
	else if (uchKey == ' ') {
		if (!g_startSelect) {

			if (g_lineNum >= 40)
			{
				g_finish = true;
				return;
			}

			g_lines[g_lineNum * 2].x = g_lines[g_lineNum * 2 + 1].x = iXPos;
			g_lines[g_lineNum * 2].y = g_lines[g_lineNum * 2 + 1].y = defSCREEN_HEIGHT - iYPos;

			g_lineNum++;
			g_startSelect = true;
		}
		else {//g_startSelect == true

			g_lines[g_lineNum * 2 - 1].x = iXPos;
			g_lines[g_lineNum * 2 - 1].y = defSCREEN_HEIGHT - iYPos;
			g_startSelect = false;
			g_endSelect = true;
		}
	}
	else if (uchKey == 'c' || uchKey == 'C') {//����
		g_lineNum = 0;
		g_startSelect = g_endSelect = g_finish = false;
	}
	glutPostRedisplay();

}
void Reshape(int w, int h) //���ڴ�С�ı��Ļص�����
{
	defSCREEN_WIDTH = w;
	defSCREEN_HEIGHT = h;
	glViewport(0.0, 0.0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, w, 0.0, h, 1, -1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void MyInit(void)
{
	g_lineNum = 0;
	g_startSelect = g_endSelect = g_finish = false;
	g_lines = (wcPt2D*)malloc(100 * sizeof(wcPt2D));
}
void PassiveMotionFunc(int iXPos, int iYPos)//���û�б�����ȥʱ,�Ƶ���������
{
	if (!g_finish) {//���û����ɿ��Ƶ��ѡ��
		if (g_startSelect) {
			g_lines[g_lineNum * 2 - 1].x = iXPos;
			g_lines[g_lineNum * 2 - 1].y = defSCREEN_HEIGHT - iYPos;
			glutPostRedisplay();
		}
	}
}
void MidPLine(int x0, int y0, int x1, int y1, void (*SetPixel)(int x, int y))
{
	//����1���˴���д����
	int k = 0;
	if (fabs(x1 - x0) < fabs(y1 - y0)) {
		swap(x0, y0);
		swap(x1, y1);
		k = 1;
	}
	if (x0 > x1)
	{
		int tmp = x0;
		x0 = x1;
		x1 = tmp;
		tmp = y0;
		y0 = y1;
		y1 = tmp;
	}
	const int a = y0 - y1;
	const int b = x1 - x0;
	int d = a + b / 2;
	int x, y;
	if (y0 < y1) {
		x = x0;
		y = y0;
		SetPixel(x, y);
		while (x < x1) {
			if (d < 0) {
				x++; y++;
				d = d + a + b;
			}
			else {
				x++;
				d += a;
			}
			if (k) SetPixel(y, x);
			else SetPixel(x, y);
		}
	}
	else {
		x = x1;
		y = y1;
		SetPixel(x, y);
		while (x > x0) {
			if (d < 0) {
				x--;
				y++;
				d = d - a + b;
			}
			else {
				x--;
				d -= a;
			}
			if (k) SetPixel(y, x);
			else SetPixel(x, y);
		}
	}
}
void BresLine(int x0, int y0, int x1, int y1, void (*SetPixel)(int x, int y)) {
	/*while (curx <= x1)
	{
		if (d < 0) d += dS;
		else { cury = cury + 1; d += dT; }
		SetPixel(curx, cury);
		curx = curx + 1;
	}*/
	//����2���˴���д���룬PPT�����㷨
	SetPixel(x0, y0);
	int dx = abs(x0 - x1);
	int dy = abs(y0 - y1);
	int flag = 0;
	if (dx < dy) {
		flag = 1;
		int tmp = x0;
		x0 = y0;
		y0 = tmp;
		tmp = x1;
		x1 = y1;
		y1 = tmp;
		tmp = dx;
		dx = dy;
		dy = tmp;
	}
	const int tx = (x1 - x0) > 0 ? 1 : -1;
	const int ty = (y1 - y0) > 0 ? 1 : -1;
	int curx = x0;
	int cury = y0;
	int dS = 2 * dy;
	int dT = 2 * (dy - dx);
	int d = dS - dx;
	while (curx != x1) {
		if (d < 0)
			d += dS;
		else {
			cury += ty;
			d += dT;
		}
		if (flag)
			SetPixel(cury, curx);
		else
			SetPixel(curx, cury);
		curx += tx;
	}
}

//�����ԣ�x0,y0��Ϊ���ģ��ԣ�x1,y1����(x0,y0)�ľ���Ϊ�뾶��Բ
void MidPointCircle(int x0, int y0, int x1, int y1, void (*SetPixel)(int x, int y))
{
	int r = sqrt((1.0 * x1 - x0) * (1.0 * x1 - x0) + (1.0 * y1 - y0) * (1.0 * y1 - y0));
	int x = 0;
	int y = r;
	int d = 1 - r;
	Cirplot(x0, y0, x, y, SetPixel);
	while (x < y)
	{
		if (d < 0)
			d += 2 * x + 3;
		else {
			d += 2 * (x - y) + 5;
			y--;
		}
		x++;
		Cirplot(x0, y0, x, y, SetPixel);
	}
}
//�����ԣ�x0,y0��Ϊ���ģ��ԣ�x1,y1����(x0,y0)��x�������Ϊx�᳤�ȣ���y�������Ϊy�᳤��
void MidPointEllipse(int x0, int y0, int x1, int y1, void (*SetPixel)(int x, int y))
{
	//����4���˴���д���룬PPT���㷨
	double a = fabs(x1 - x0);
	double b = fabs(y1 - y0);
	int x = 0, y = b;
	double d1, d2;
	d1 = b * b + a * a * (-b + 0.25);
	EllipsePoints(x0, y0, x, y, SetPixel);
	while (a * a * (y - 0.5) > b * b * (x + 1))
	{
		if (d1 < 0)  d1 += b * b * (2 * x + 3);
		else { d1 += (b * b * (2 * x + 3) + a * a * (-2 * y + 2)); y--; }
		x++;
		EllipsePoints(x0, y0, x, y, SetPixel);
	}
	d2 = sqrt(b * (x + 0.5)) + sqrt(a * (y - 1)) - sqrt(a * b);
	while (y > 0)
	{
		if (d2 < 0) { d2 += b * b * (2 * x + 2) + a * a * (-2 * y + 3); x++; }
		else { d2 += a * a * (-2 * y + 3); }
		y--;
		EllipsePoints(x0, y0, x, y, SetPixel);
	}
}
void Cirplot(int x0, int y0, int x, int y, void (*SetPixel)(int x, int y))
{
	SetPixel((x0 + x), (y0 + y));
	SetPixel((x0 + y), (y0 + x));
	SetPixel((x0 + y), (y0 - x));
	SetPixel((x0 + x), (y0 - y));
	SetPixel((x0 - x), (y0 - y));
	SetPixel((x0 - y), (y0 - x));
	SetPixel((x0 - y), (y0 + x));
	SetPixel((x0 - x), (y0 + y));
}
void EllipsePoints(int x0, int y0, int x, int y, void (*SetPixel)(int x, int y))
{
	SetPixel(x0 + x, y0 + y);
	SetPixel(x0 - x, y0 + y);
	SetPixel(x0 + x, y0 - y);
	SetPixel(x0 - x, y0 - y);
}
void lineSegment(int x0, int y0, int x1, int y1)
{
	//����5���˴���д����,���̲ĵ�4�»�PPT
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(x0, y0);
	glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(x1, y1);
	glEnd();
}