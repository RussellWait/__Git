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

	glPushMatrix();							// 把矩阵压入到矩阵的堆栈中
	glTranslatef(0.0f, 0.0f, -1.0f);		// 设定模型矩阵（向左移动）

	// 打开抗锯齿功能
	if (!glIsEnabled(GL_POINT_SMOOTH))
	{
		glEnable(GL_POINT_SMOOTH);
	}

	// 绘制点
	float nonSize;
	glGetFloatv(GL_POINT_SIZE, &nonSize);	// 获取绘制点大小
	glPointSize(15);						// 设置绘制点大小
	glBegin(GL_POINTS);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, -5.0f);
	glEnd();

	// 绘制线
	glLineWidth(16);
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glEnd();

	// 绘制虚线
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
