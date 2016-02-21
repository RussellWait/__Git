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
	glEnable(GL_AUTO_NORMAL);		// 执行后，图形能把光反射到各个方向
	glEnable(GL_NORMALIZE);			// 根据函数glNormal的设置条件，启用法向量

	glShadeModel(GL_SMOOTH);		// 着色设置
									//		GL_FLAT:	单调着色
									//		GL_SMOOTH:	平滑着色（默认）

	glDepthFunc(GL_DEPTH_TEST);		// 指定深度缓冲比较函数

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
