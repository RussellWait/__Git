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

	AUX_RGBImageRec *textureImages[1];		// ��������ͼ
											//		sizeX	ͼƬ���
											//		sizeY	ͼƬ�߶�
											//		data	ͼƬ���������ݣ��ڴ�����������ָ�룩

	if (textureImages[0] = auxDIBImageLoad(fileName))	//	��ȡ����
	{
		status = TRUE;

		// ��������
		glGenTextures(	1,					// �����������������
						&textures[0]);		// �洢���������

		// ������
		glBindTexture(	GL_TEXTURE_2D,		// ����������
						textures[0]);		// �����������������ڵ�ǰӦ���в��ܱ��ٴ�ʹ�ã�

		// �ƶ�����
		glTexImage2D(	GL_TEXTURE_2D,				// ��������
						0,							// ִ��ϸ�ڼ���0���������ͼ�񼶱�
						3,							// ������ɫ���
						textureImages[0]->sizeX,	// ָ������ͼ��Ŀ��
						textureImages[0]->sizeY,	// �ƶ�����ͼ��ĸ߶�
						0,							// �߿��ȣ�����Ϊ0��
						GL_RGB,						// ��������ɫ������Ӧ
						GL_UNSIGNED_BYTE,			// �ƶ�������������
						textureImages[0]->data);	// �ڴ�����������ָ��

		// ���Ŵ���ʽ���Ŵ�ʱ�������Թ��˷�ʽ��
		glTexParameteri(GL_TEXTURE_2D,				// ��������
						GL_TEXTURE_MIN_FILTER,		// ����ʽ
													//		GL_TEXTURE_WRAP_S		S�����ϵ���ͼģʽ
													//		GL_TEXTURE_WRAP_T		T�����ϵ���ͼģʽ
													//		GL_TEXTURE_CLAMP		����������������0.0~1.0֮��
													//		GL_TEXTURE_MIN_FILTER	��С����
													//		GL_TEXTURE_MAG_FILTER	�Ŵ����
						GL_LINEAR);					// ���Թ���

		// ���Ŵ���ʽ����Сʱ�������Թ��˷�ʽ��
		glTexParameteri(GL_TEXTURE_2D,
						GL_TEXTURE_MAG_FILTER,
						GL_LINEAR);
	}

	// �ͷ�
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

	// ������
	glBindTexture(GL_TEXTURE_2D, textures[0]);

	// ����Ӱ��
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
