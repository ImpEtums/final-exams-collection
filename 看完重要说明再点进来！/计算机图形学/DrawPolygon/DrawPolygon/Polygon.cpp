#include <gl/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include "Polygon.h"
#include "common.h"
#include "math.h"

struct vertex { 
    float ver_x;
    float ver_y;
};
typedef struct XET { 
    float x;
    float dx, ymax;
    XET* next;
}AET, NET;

vertex* ver;
//����йض����ɨ��ת���ĺ���

//��OpenGL�������ƶ����
void DrawPolygonOpenGL(int g_iCtrlPntNum, wcPt2D	g_pCtrlPoints[])
{
	 glColor3f(1.0,0,0.0);
	//�ڴ���д���룬����Ҳ��Ҫ������������
	 glShadeModel(GL_SMOOTH);
	 glClear(GL_COLOR_BUFFER_BIT);
	 glBegin(GL_POLYGON);
	 for (int i = 0; i < g_iCtrlPntNum; i++) {
		 glVertex2f(g_pCtrlPoints[i].x, g_pCtrlPoints[i].y);
	 }
	 glEnd();
	 glFlush();
}


//��ͬѧ��ʵ��DrawPolygon��������ɶ���ε�ɨ��ת���㷨
//ͬʱҲҪʵ�ֱ߱�ͻ�߱�����ݽṹ����Ӧ�㷨
//����������g_iCtrlPntNum����������ֵ����g_pCtrlPoints������
//!!!ע��!!!����M������ѡ������һ������ ���� ��һ�����㣬
//��g_pCtrlPoints[g_iCtrlPntNum-1] �� g_pCtrlPoints[0]����ͬ��
//���ı���Ϊ����g_iCtrlPntNum=5�����g_pCtrlPoints[0]���յ�g_pCtrlPoints[4]ָͬһ����
//DrawPolygon����PPT�ϵ�FillPolygonbyAET�����������PPT���㷨ʵ��
void DrawPolygon(int g_iCtrlPntNum, wcPt2D	g_pCtrlPoints[])
{
	//�ڴ���д���룬����Ҳ��Ҫ������������
    int MaxY = 0;
    int i, n = g_iCtrlPntNum;
    ver = (vertex*)malloc(sizeof(vertex) * n);

    for (int i = 0; i < n; i++) {
        ver[i].ver_x = g_pCtrlPoints[i].x;
        ver[i].ver_y = g_pCtrlPoints[i].y;
    }
    for (i = 0; i < n; i++) {
        if (ver[i].ver_y > MaxY)
            MaxY = ver[i].ver_y;
    }

    AET* pAET = new AET;
    pAET->next = NULL;

    NET* pNET[1024];
    for (i = 0; i <= MaxY; i++) {
        pNET[i] = new NET;
        pNET[i]->next = NULL;
    }


    for (i = 0; i < MaxY; i++) {
		for (int j = 0; j < n; j++) {
            if (ver[j].ver_y == i) {
                if (ver[(j + 1 + n) % n].ver_y > ver[j].ver_y) {
                    NET* p = new NET;
                    p->x = ver[j].ver_x;
                    p->ymax = ver[(j + 1 + n) % n].ver_y;
                    p->dx = (ver[(j + 1 + n) % n].ver_x - ver[j].ver_x) / (ver[(j + 1 + n) % n].ver_y - ver[j].ver_y);
                    p->next = pNET[i]->next;
                    pNET[i]->next = p;
                }
                if (ver[(j - 1 + n) % n].ver_y > ver[j].ver_y) {
                    NET* p = new NET;
                    p->x = ver[j].ver_x;
                    p->ymax = ver[(j - 1 + n) % n].ver_y;
                    p->dx = (ver[(j - 1 + n) % n].ver_x - ver[j].ver_x) / (ver[(j - 1 + n) % n].ver_y - ver[j].ver_y);
                    p->next = pNET[i]->next;
                    pNET[i]->next = p;
                }
            }
        }
    }
    for (i = 0; i <= MaxY; i++) {
        AET* p = new AET;
        p = pAET->next;
        AET* n = new AET;
        if (pNET[i]->next && pNET[i]->next->next) {
            if (pNET[i]->next->dx > 0) {
                NET* t = new NET;
                t = pNET[i]->next;
                n = pNET[i]->next->next;
                t->next = NULL;
                n->next = NULL;
                pNET[i]->next = n;
                n->next = t;
            }
        }
        while (p) {
            p->x = p->x + p->dx;
            p = p->next;
        }
        p = pAET->next;
        n = pAET;
        while (p) {
            if (p->ymax == i) {
                n->next = p->next;
                free(p);
                p = n->next;
            }
            else {
                p = p->next;
                n = n->next;
            }
        }
        p = pAET->next;
        n = pAET;
        NET* a = new NET;
        a = pNET[i]->next;
        if (a) {
            NET* b = new NET;
            b = a;
            while (b->next) {
                b = b->next;
            }
            if (!pAET->next) {
                pAET->next = a;
            }
            else {
                while (p) {
                    if (a->x < p->x) {
                        b->next = p;
                        n->next = a;
                        break;
                    }
                    if (!p->next) {
                        p->next = a;
                        break;
                    }
                    n = n->next;
                    p = p->next;
                }
            }
		}
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1.0, 0, 0.0);
        glBegin(GL_POINTS);
        p = pAET->next;
        while (p && p->next) {
            for (float j = p->x; j <= p->next->x; j++)
                glVertex2i(static_cast<int>(j), i);
            p = p->next->next;
        }

    }
    glEnd();
    glFlush();
}