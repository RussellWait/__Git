#include "3D_Function.h"
#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/GLAUX.H>


GLfloat	rotate_ange = 0.0f;


void InitOpenGL()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void SetupMatrices(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLdouble)w/(GLdouble)h, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Render()
{
	// 使用默认数据填充
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 调整观察矩阵
	glLoadIdentity();
	gluLookAt(	0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, -1.0f,
				0.0f, 1.0f, 0.0f);

	// 开启防锯齿
	if (!glIsEnabled(GL_POLYGON_SMOOTH))
	{
		glEnable(GL_POLYGON_SMOOTH);
	}

	// 调整模型位置
	glTranslated(0.0f, -0.5f, -3.0f);

	// 调整模型角度
	glRotatef(rotate_ange, 0.0f, 1.0f, 0.0f);
	rotate_ange += 0.5f;

	// 确定哪个是正面（参数表明绘制顺序）
	glFrontFace(GL_CW);		// GL_CW 顺时针，GL_CCW 逆时针

	// 控制多边形的显示方式
	glPolygonMode(	GL_FRONT,		// 表示适用于哪些部分
									//		GL_FRONT			适用于前向面
									//		GL_BACK				适用于后相面
									//		GL_FRONT_AND_BACK	适用于前后相面
					GL_LINE);		// 选中的部分以何种方式显示
									//		GL_POINT			只显示顶点
									//		GL_LINE				显示线段
									//		GL_FILL				显示面（多边形采用填充的形式）
	
	// 是否显示多边形的边
	glEdgeFlag(GL_FALSE);

	// 打开隐面剪切功能
	if (!glIsEnabled(GL_CULL_FACE))
	{
		glIsEnabled(GL_CULL_FACE);
	}
	
	// 对背面进行隐面操作
	glCullFace(GL_BACK);

	// 绘制三角形
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glEnd();
}
