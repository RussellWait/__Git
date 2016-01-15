#include "3D_Function.h"

#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/GLAUX.H>

void SetupMatrices(int w, int h)
{
	glMatrixMode(GL_PROJECTION);	// ���������������ʹ��ʲô�任
									//		GL_PROJECTION		ͶӰ����

	// ʹ��ǰ��Ҫ���þ��󣬱�֤��û�б�ʹ�ù���Ĭ�����õ���G_MODELVIEW
	glLoadIdentity();

	// �������ǵ�ͶӰ����
	gluPerspective(	45.0f,					// �ӽǿ��
					(GLfloat)w/(GLfloat)h,	// ���ڵĿ�߱�
					0.1f,					// ���ü�����۾��ľ���
					100.0f);				// Զ�ü�����۾��ľ���

	// OpenGL��û�аѹ۲�������������������������ģ�͹۲�ľ���
	// ��������Ҫʹ���������͹۲���󣬾�Ҫ����ģ�;���ſ���ʵ������Ӧ�Ĳ���
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// ���ù۲�����趨�������λ�úͳ���
	gluLookAt(	0.0f, 0.0f, 0.0f,			// ��������������λ�ã��Դ�λ�ã�
				0.0f, 0.0f, -100.0f,		// �����ͷ��׼�����������������λ�ã�������ĳ����۾����ߣ�
				0.0f, 1.0f, 0.0f);			// ������ϵķ��������������еķ���ͷ�����򡣡�����������������ͷ��
}
