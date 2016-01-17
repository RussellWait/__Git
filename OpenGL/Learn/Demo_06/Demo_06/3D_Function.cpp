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
	// ʹ��Ĭ���������
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// �����۲����
	glLoadIdentity();
	gluLookAt(	0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, -1.0f,
				0.0f, 1.0f, 0.0f);

	// ���������
	if (!glIsEnabled(GL_POLYGON_SMOOTH))
	{
		glEnable(GL_POLYGON_SMOOTH);
	}

	// ����ģ��λ��
	glTranslated(0.0f, -0.5f, -3.0f);

	// ����ģ�ͽǶ�
	glRotatef(rotate_ange, 0.0f, 1.0f, 0.0f);
	rotate_ange += 0.5f;

	// ȷ���ĸ������棨������������˳��
	glFrontFace(GL_CW);		// GL_CW ˳ʱ�룬GL_CCW ��ʱ��

	// ���ƶ���ε���ʾ��ʽ
	glPolygonMode(	GL_FRONT,		// ��ʾ��������Щ����
									//		GL_FRONT			������ǰ����
									//		GL_BACK				�����ں�����
									//		GL_FRONT_AND_BACK	������ǰ������
					GL_LINE);		// ѡ�еĲ����Ժ��ַ�ʽ��ʾ
									//		GL_POINT			ֻ��ʾ����
									//		GL_LINE				��ʾ�߶�
									//		GL_FILL				��ʾ�棨����β���������ʽ��
	
	// �Ƿ���ʾ����εı�
	glEdgeFlag(GL_FALSE);

	// ��������й���
	if (!glIsEnabled(GL_CULL_FACE))
	{
		glIsEnabled(GL_CULL_FACE);
	}
	
	// �Ա�������������
	glCullFace(GL_BACK);

	// ����������
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glEnd();
}
