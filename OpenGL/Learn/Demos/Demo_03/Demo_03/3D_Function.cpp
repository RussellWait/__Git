#include "3D_Function.h"

#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/GLAUX.H>
#include <stdio.h>

void InitOpenGL()
{
	// ָ�������ɫ��ͨ��glClearʹ�ø���ɫ�����������
	glClearColor(1.0f, 0.0f, 0.0f, 0.5f);

	// ָ����Ȼ�������ֵ�������е�ÿ�����ص����ֵ�������ֵ
	glClearDepth(1.0f);

	glEnable(GL_DEPTH_TEST);	// ���ø���ܣ����幦���ɲ�������
								// ��glDisable���Ӧ��glDisable���Թرո����
								// ʹ��glIsEnabled��ȷ����ǰ����ܵĿ������
								// glEnable����д��glBegin��glEnd֮��

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// ��ͼ�����ٶ�֮��ѡ��
														//	GL_POINT_SMOOTH_HINT
														//	GL_LINE_SHOOTH_HINT
														//	GL_POLYGON_SMOOTH_HINT
														//	������������ָ���ڽ��з���ݲ����� �㡢�ߡ�����εĳ�������
														//		
														//	GL_FOG_HINT������ļ��㽫���������ƻ��Ƕ�������ִ��ȡ���ڵڶ�������
														//		GL_FASTERST		--�Զ�����ʽ
														//		GL_NICEST		--��������ʽִ��
														//
														//	GL_PERSPECTIVE_CORRECTION_HINT��ָ����ɫ����������Ĳ�ֵƷ��
														//		GL_NICEST		--���Ʒ��
														//		GL_DONT_CARE	--��OpenGL�����Լ�����
														//		GL_FASTEST		--ʹ������ٺ����Ч����ʵ��
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
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// �����������
														//		GL_COLOR_BUFFER_BIT		��ǰ��д����ɫ����
														//		GL_DEPTH_BUFFER_BIT		��Ȼ���
														//		GL_ACCUM_BUFFER_BIT		�ۻ�����
														//		GL_STENCIL_BUFFER_BIT	ģ�建��

	glLoadIdentity();
	gluLookAt(	0.0f, 0.0f, 0.0f,
				0.0f, 0.0f,	-100.0f,
				0.0f, 1.0f, 0.0f);
}
