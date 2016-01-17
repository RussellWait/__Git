#include "3D_Function.h"

#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/GLAUX.H>
#include <stdio.h>

void InitOpenGL()
{
	// 指定清除颜色，通过glClear使用该颜色来清除缓冲区
	glClearColor(1.0f, 0.0f, 0.0f, 0.5f);

	// 指定深度缓冲区数值，缓冲中的每个像素的深度值都是这个值
	glClearDepth(1.0f);

	glEnable(GL_DEPTH_TEST);	// 启用各项功能，具体功能由参数决定
								// 与glDisable相对应，glDisable用以关闭各项功能
								// 使用glIsEnabled来确定当前各项功能的开启情况
								// glEnable不能写在glBegin和glEnd之间

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// 在图像与速度之间选择
														//	GL_POINT_SMOOTH_HINT
														//	GL_LINE_SHOOTH_HINT
														//	GL_POLYGON_SMOOTH_HINT
														//	以上三个参数指定在进行反锯齿操作中 点、线、多边形的抽样质量
														//		
														//	GL_FOG_HINT：烟雾的计算将以像素形势还是顶点形势执行取决于第二个参数
														//		GL_FASTERST		--以顶点形式
														//		GL_NICEST		--以像素形式执行
														//
														//	GL_PERSPECTIVE_CORRECTION_HINT：指定颜色与纹理坐标的插值品质
														//		GL_NICEST		--最高品质
														//		GL_DONT_CARE	--由OpenGL驱动自己决定
														//		GL_FASTEST		--使用最快速和最高效率来实现
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
	glClearColor((rand()%255)/255.0, (rand()%255)/255.0, (rand()%255)/255.0, (rand()%255)/255.0);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// 清除缓冲区域
														//		GL_COLOR_BUFFER_BIT		当前可写的颜色缓冲
														//		GL_DEPTH_BUFFER_BIT		深度缓冲
														//		GL_ACCUM_BUFFER_BIT		累积缓冲
														//		GL_STENCIL_BUFFER_BIT	模板缓冲

	glLoadIdentity();
	gluLookAt(	0.0f, 0.0f, 0.0f,
				0.0f, 0.0f,	-100.0f,
				0.0f, 1.0f, 0.0f);
}
