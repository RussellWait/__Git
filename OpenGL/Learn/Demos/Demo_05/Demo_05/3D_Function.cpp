#include "3D_Function.h"
#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/GLAUX.H>


void InitOpenGL()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void SetupMatrices(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)w/(GLfloat)h, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(	0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, -100.0f,
				0.0f, 1.0f, 0.0f);

	glPushMatrix();							// �Ѿ���ѹ�뵽����Ķ�ջ��
	glTranslatef(0.0f, 0.0f, -1.0f);		// �趨ģ�;��������ƶ���

	// �򿪿���ݹ���
	if (!glIsEnabled(GL_POINT_SMOOTH))
	{
		glEnable(GL_POINT_SMOOTH);
	}

	// ���Ƶ�
	float nonSize;
	glGetFloatv(GL_POINT_SIZE, &nonSize);	// ��ȡ���Ƶ��С
	glPointSize(15);						// ���û��Ƶ��С
	glBegin(GL_POINTS);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, -5.0f);
	glEnd();

	// ������
	glLineWidth(16);
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glEnd();

	// ��������
	glEnable(GL_LINE_STIPPLE);
	int stipplePattern = 0xAAAA;	// 1010 1010 1010 1010
	glLineStipple(10, stipplePattern);
	glBegin(GL_LINES);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(2.0f, -1.0f, -2.0f);
	glVertex3f(-2.0f, 1.0f, -2.0f);
	glEnd();
	glDisable(GL_LINE_STIPPLE);

	glPopMatrix();
}
