#include "3D_Function.h"

#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/GLAUX.H>

void SetupMatrices(int w, int h)
{
	glMatrixMode(GL_PROJECTION);	// 这个函数解释我们使用什么变换
									//		GL_PROJECTION		投影矩阵

	// 使用前需要重置矩阵，保证其没有被使用过，默认重置的是G_MODELVIEW
	glLoadIdentity();

	// 设置我们的投影矩阵
	gluPerspective(	45.0f,					// 视角宽度
					(GLfloat)w/(GLfloat)h,	// 窗口的宽高比
					0.1f,					// 近裁剪面距眼睛的距离
					100.0f);				// 远裁剪面距眼睛的距离

	// OpenGL中没有把观察矩阵和世界矩阵独立开，而是用模型观察的矩阵
	// 所以我们要使用世界矩阵和观察矩阵，就要设置模型矩阵才可以实现其相应的操作
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// 设置观察矩阵，设定摄像机的位置和朝向
	gluLookAt(	0.0f, 0.0f, 0.0f,			// 相机在世界坐标的位置（脑袋位置）
				0.0f, 0.0f, -100.0f,		// 相机镜头对准的物体在世界坐标的位置，摄像机的朝向（眼睛视线）
				0.0f, 1.0f, 0.0f);			// 相机向上的方向在世界坐标中的方向（头顶朝向。。。。。。可以歪着头）
}
