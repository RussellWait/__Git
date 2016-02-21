#include "3D_Function.h"
#include <windows.h>
#include <gl/GL.H>
#include <gl/GLU.H>
#include <gl/GLAUX.H>
#include "MD2.h"


extern CMD2     g_MD2;


void InitOpenGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
    glClearDepth(1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
	glEnable(GL_AUTO_NORMAL);		// ִ�к�ͼ���ܰѹⷴ�䵽��������
	glEnable(GL_NORMALIZE);			// ���ݺ���glNormal���������������÷�����

	glShadeModel(GL_SMOOTH);		// ��ɫ����
									//		GL_FLAT:	������ɫ
									//		GL_SMOOTH:	ƽ����ɫ��Ĭ�ϣ�

	glDepthFunc(GL_DEPTH_TEST);		// ָ����Ȼ���ȽϺ���

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void SetupMatrices(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLdouble)w / (GLdouble)h, 0.1f, 1000.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

float rotate_angle = 0.0f;
void Render()
{
    static unsigned int uiStartFrame = 0, uiEndFrame = 182;
    static float fAnimSpeed = 16.0f;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f, -0.75f, -5.0f);
	glRotatef(rotate_angle, 0.0f, 1.0f, 0.0f);
	rotate_angle -= 0.1f;

    //g_MD2.Render();
    g_MD2.Animate(fAnimSpeed, uiStartFrame, uiEndFrame, true);
}
