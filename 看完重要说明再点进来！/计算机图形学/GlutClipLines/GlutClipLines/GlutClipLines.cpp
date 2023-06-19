#include <gl/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "math.h"



int defSCREEN_WIDTH = 800, defSCREEN_HEIGHT = 800;
int g_lineNum;
bool g_startSelect, g_endSelect, g_finish;
wcPt2D* g_lines;
GLint Left = 0x1;
GLint Right = 0x2;
GLint Bottom = 0x4;
GLint Top = 0x8;


void Display();
void Reshape(int w, int h);
void Keyboard(unsigned char uchKey, int iXPos, int iYPos);
void PassiveMotionFunc(int iXPos, int iYPos);
void MyInit(void);
void SetPixel(int x, int y);
void BresLine(int x0, int y0, int x1, int y1, void (*SetPixel)(int x, int y));
GLubyte encode(wcPt2D pt, wcPt2D winMin, wcPt2D winMax);
GLint clipTest(GLfloat p, GLfloat q, GLfloat* u1, GLfloat* u2);
void lineClipLB(wcPt2D winMin, wcPt2D winMax, wcPt2D& p1, wcPt2D& p2);
void lineClipC(wcPt2D winMin, wcPt2D winMax, wcPt2D& p1, wcPt2D& p2);

void swapP(wcPt2D* p1, wcPt2D* p2)
{
	wcPt2D t;
	t = *p1; *p1 = *p2; *p2 = t;
}
void swapC(GLubyte* c1, GLubyte* c2)
{
	GLubyte t;
	t = *c1; *c1 = *c2; *c2 = t;
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	MyInit();
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(defSCREEN_WIDTH, defSCREEN_HEIGHT);

	int windowHandle = glutCreateWindow("Glut Clip Lines ");
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
	glColor3f(1.0, 0, 0);
	glLineWidth(5.0);//�����߿���
	glBegin(GL_LINE_LOOP);//���Ʋü�����
	glVertex2f(50, 50);
	glVertex2f(50, 600);
	glVertex2f(600, 600);
	glVertex2f(600, 50);
	glEnd();

	glPointSize(1.0);//���õ����
	glColor3f(0, 0, 1.0);//���õ���ɫ����
	for (int i = 0; i < g_lineNum; i++)
	{
		BresLine(g_lines[i * 2].x, g_lines[i * 2].y, g_lines[i * 2 + 1].x, g_lines[i * 2 + 1].y, SetPixel);
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
	else if (uchKey == 't' || uchKey == 'T') {//ֱ�߶βü�
		wcPt2D winMin, winMax;
		winMin.x = 50;
		winMin.y = 50;
		winMax.x = 600;
		winMax.y = 600;
		for (int i = 0; i < g_lineNum; i++)
		{
			lineClipLB(winMin, winMax, g_lines[i * 2], g_lines[i * 2 + 1]);
			//lineClipC(winMin, winMax, g_lines[i * 2], g_lines[i * 2 + 1]);
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

void BresLine(int x0, int y0, int x1, int y1, void (*SetPixel)(int x, int y)) {
	SetPixel(x0, y0);
	// �����ʼ��(x0,y0)
	int flag = 0;
	int dx = abs(x0 - x1);	// ��ʾ����x�᷽���ϵĲ�ֵ
	int dy = abs(y0 - y1);	// ��ʾ����y�᷽���ϵĲ�ֵ
	// ��(x0,y0)(x1,y1)��ʾͬһ����ʱ���˳�������
	if (dx < dy) {	// ���潫б�ʱ任��0��حkح��1����
		flag = 1;	// �������حkح>=1����x1,x2��ʾy��ĵ�;y1,y2��ʾx��ĵ㣬��y��Ϊ�Ƴ�����
		swap(x0, y0);
		swap(x1, y1);
		swap(dx, dy);
	}
	int tx = (x1 - x0) > 0 ? 1 : -1;	// tx��ʾֱ������������x��ķ���
	int ty = (y1 - y0) > 0 ? 1 : -1;	// ty��ʾֱ������������y��ķ���
	int curx = x0;
	int cury = y0;
	int dS = 2 * dy;			// ���ڱ�ʾ����ʽ�е���
	int dT = 2 * (dy - dx);		// ���ڱ�ʾ����ʽ�е���
	int d = dS - dx;			// ���ڱ�ʾ����ʽ�е���
	while (curx != x1) {
		if (d < 0)				// ȡֱ���·������ص�
			d += dS;
		else {					// ȡֱ���Ϸ������ص�
			cury += ty;
			d += dT;
		}
		if (flag) SetPixel(cury, curx);
		else
			SetPixel(curx, cury);
		curx += tx;
	}

}

GLint clipTest(GLfloat p, GLfloat q, GLfloat* u1, GLfloat* u2) {
	GLfloat r;
	GLint returnValue = true;
	if (p < 0.0) {
		r = q / p;
		if (r > *u2)
			returnValue = false;
		else
			if (r > *u1)
				*u1 = r;
	}
	else
		if (p > 0.0) {
			r = q / p;
			if (r < *u1)
				returnValue = false;
			else if (r < *u2)
				*u2 = r;
		}
		else
			if (q < 0.0)
				returnValue = false;

	return(returnValue);
}

void lineClipLB(wcPt2D winMin, wcPt2D winMax, wcPt2D& p1, wcPt2D& p2)
{
	GLfloat u1 = 0.0, u2 = 1.0, dx = p2.x - p1.x, dy;
	if (clipTest(-dx, p1.x - winMin.x, &u1, &u2))
		if (clipTest(dx, winMax.x - p1.x, &u1, &u2)) {
			dy = p2.y - p1.y;
			if (clipTest(-dy, p1.y - winMin.y, &u1, &u2))
				if (clipTest(dy, winMax.y - p1.y, &u1, &u2)) {
					if (u2 < 1.0) {
						p2.x = p1.x + u2 * dx;
						p2.y = p1.y + u2 * dy;
					}
					if (u1 > 0.0) {
						p1.x = p1.x + u1 * dx;
						p1.y = p1.y + u1 * dy;
					}

				}
		}
}

GLubyte encode(wcPt2D pt, wcPt2D winMin, wcPt2D winMax)
{
	GLubyte code = 0x00;
	if (pt.x < winMin.x)
		code = code | Left;
	if (pt.x > winMax.x)
		code = code | Right;
	if (pt.y < winMin.y)
		code = code | Bottom;
	if (pt.y > winMax.y)
		code = code | Top;
	return (code);
}

void lineClipC(wcPt2D winMin, wcPt2D winMax, wcPt2D& p1, wcPt2D& p2)
{
	GLubyte code1, code2;
	GLint done = false, plotLine = false;
	GLfloat m;
	while (!done) {
		code1 = encode(p1, winMin, winMax);
		code2 = encode(p2, winMin, winMax);
	}
	if (!(code1 | code2)) {
		done = true;
		plotLine = true;
	}
	else
		if (code1 & code2)
			done = true;
		else
		{
			if (!code1) {
				swapP(&p1, &p2);
				swapC(&code1, &code2);
			}
			if (p2.x != p1.x)
				m = (p2.y - p1.y) / (p2.x - p1.x);
			if (code1 & Left) {
				p1.y += (winMin.x - p1.x) * m;
				p1.x = winMin.x;
			}
			else
				if (code1 & Right) {
					p1.y += (winMax.x - p1.x) * m;
					p1.x = winMax.x;
				}
				else
					if (code1 & Bottom) {
						if (p2.x != p1.x)
							p1.x += (winMin.y - p1.y) / m;
						p1.y = winMin.y;
					}
					else
						if (code1 & Top) {
							{
								if (p2.x != p1.x)
									p1.x += (winMax.y - p1.y) / m;
								p1.y = winMax.y;
							}
						}
		}
}