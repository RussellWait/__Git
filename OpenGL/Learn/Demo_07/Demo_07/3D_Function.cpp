#include "3D_Function.h"
#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/GLAUX.H>


GLuint textures[1];


void InitOpenGL()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
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

int LoadGLTextures(char *fileName)
{
	int status = FALSE;

	AUX_RGBImageRec *textureImages[1];		// 描述纹理图
											//		sizeX	图片宽度
											//		sizeY	图片高度
											//		data	图片包含的数据（内存中像素数据指针）

	if (textureImages[0] = auxDIBImageLoad(fileName))	//	读取纹理
	{
		status = TRUE;

		// 创建纹理
		glGenTextures(	1,					// 用来生成纹理的数量
						&textures[0]);		// 存储纹理的索引

		// 绑定纹理
		glBindTexture(	GL_TEXTURE_2D,		// 绑定纹理类型
						textures[0]);		// 纹理索引（该索引在当前应用中不能被再次使用）

		// 制定纹理
		glTexImage2D(	GL_TEXTURE_2D,				// 纹理类型
						0,							// 执行细节级别（0是最基本的图像级别）
						3,							// 纹理颜色组件
						textureImages[0]->sizeX,	// 指定纹理图像的宽度
						textureImages[0]->sizeY,	// 制定纹理图像的高度
						0,							// 边框宽度（必须为0）
						GL_RGB,						// 与纹理颜色组件相对应
						GL_UNSIGNED_BYTE,			// 制定像素数据类型
						textureImages[0]->data);	// 内存中像素数据指针

		// 缩放处理方式（放大时采用线性过滤方式）
		glTexParameteri(GL_TEXTURE_2D,				// 纹理类型
						GL_TEXTURE_MIN_FILTER,		// 处理方式
													//		GL_TEXTURE_WRAP_S		S方向上的贴图模式
													//		GL_TEXTURE_WRAP_T		T方向上的贴图模式
													//		GL_TEXTURE_CLAMP		将纹理坐标限制在0.0~1.0之内
													//		GL_TEXTURE_MIN_FILTER	缩小过滤
													//		GL_TEXTURE_MAG_FILTER	放大过滤
						GL_LINEAR);					// 线性过滤

		// 缩放处理方式（缩小时采用线性过滤方式）
		glTexParameteri(GL_TEXTURE_2D,
						GL_TEXTURE_MAG_FILTER,
						GL_LINEAR);
	}

	// 释放
	if (textureImages[0])
	{
		if (textureImages[0]->data)
		{
			free(textureImages[0]->data);
		}

		free(textureImages[0]);
	}

	return status;
}

void Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(	0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, -100.0f,
				0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, -5.0f);

	// 绑定纹理
	glBindTexture(GL_TEXTURE_2D, textures[0]);

	// 坐标影视
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glEnd();
}
