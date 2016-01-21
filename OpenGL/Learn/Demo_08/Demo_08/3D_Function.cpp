#include "3D_Function.h"
#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/GLAUX.H>


GLuint textures[1];
float dist = 0.0f;
float speed = -0.5;


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

	AUX_RGBImageRec *textureImages[1];
	if (textureImages[0] = auxDIBImageLoad(fileName))
	{
		glGenTextures(1, textures);
		glBindTexture(GL_TEXTURE_2D, textures[0]);
		glTexImage2D(	GL_TEXTURE_2D,
						0,
						3,
						textureImages[0]->sizeX,
						textureImages[0]->sizeY,
						0,
						GL_RGB,
						GL_UNSIGNED_BYTE,
						textureImages[0]->data);

		// ��С����
		glTexParameteri(	GL_TEXTURE_2D, 
							GL_TEXTURE_MIN_FILTER, 
							GL_LINEAR_MIPMAP_NEAREST);	//	���˷�ʽ
														//		GL_NEAREST					��mip���㣬ʹ���ڽ�����
														//		GL_LINEAR					��mip���㣬ʹ�����Թ���
														//		GL_NEAREST_MIPMAP_NEAREST	�����ڽ�mip�㣬ʹ���ڽ�����
														//		GL_NEAREST_MIPMAP_LINEAR	��mip��֮����в�ֵ����ʹ���ڽ�����
														//		GL_LINEAR_MIPMAP_NEAREST	�����ڽ�mip�㣬ʹ�����Թ���
														//		GL_LINEAR_MIPMAP_LINEAR		��mip��֮����в�ֵ����ʹ�����Թ���

		// �Ŵ����
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// �㼶��ͼ����
		gluBuild2DMipmaps(	GL_TEXTURE_2D,				// ָ����������
							GL_RGB,						// ��ɫ�ɷ�
							256,						// ������
							256,						// ����߶�
							GL_RGB,						// ȷ��������ɫ��ʽ
							GL_UNSIGNED_BYTE,			// ����ͼ�����������
							textureImages[0]->data);	// ��������
	}

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
				0.0f, 0.0f, -1.0f,
				0.0f, 1.0f, 1.0f);
	glTranslated(0.0f, 0.0f, dist);

	glBindTexture(GL_TEXTURE_2D, textures[0]);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0, 0.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glEnd();

	dist += speed;
	if (dist == 0 || dist == -100)
	{
		speed = -speed;
	}
}
