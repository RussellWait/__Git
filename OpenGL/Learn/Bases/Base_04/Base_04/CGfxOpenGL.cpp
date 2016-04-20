#include "CGfxOpenGL.h"

#include <math.h>
#include <windows.h>
#include <gl/GL.H>
#include <gl/GLU.H>


CGfxOpenGL::CGfxOpenGL()
{}

CGfxOpenGL::~CGfxOpenGL()
{}

bool CGfxOpenGL::Init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);		// ���ñ���ɫ

    return true;
}

bool CGfxOpenGL::Shutdown()
{
    return true;
}

// ���ô��ڿ��
void CGfxOpenGL::SetupProjection(int width, int height)
{
    // ���ڸ߶�����Ϊ1
    if ( 0 == height )
    {
        height = 1;
    }

    // ����λ�����С
    glViewport(0, 0, width, height);

    // ͶӰ����
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // �����ӽǴ�С�����ڿ�߱ȣ�ǰ����ʾ����
    gluPerspective(52.0f, (GLfloat)width / (GLdouble)height, 1.0f, 1000.0f);

    // ����Ϊģ�;��󲢳�ʼ��
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    m_windowWidth = width;
    m_windowHeight = height;
}

void CGfxOpenGL::Prepare(float dt)
{

}

void CGfxOpenGL::Render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(0.0f, 0.0f, 0.0f,
              0.0f, 0.0f, 0.0f,
              0.0f, 0.0f, 0.0f);

}
