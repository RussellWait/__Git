#include "CGfxOpenGL.h"

#include <windows.h>
#include <math.h>
#include <gl/GL.H>
#include <gl/GLU.H>


#pragma warning(disable:4305)

CGfxOpenGL::CGfxOpenGL()
{}

CGfxOpenGL::~CGfxOpenGL()
{}

// ��ʼ��opengl
bool CGfxOpenGL::Init()
{
    // ���ñ���ɫ �� ģ�ͳ�ʼ�Ƕ�
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    m_angle = 0.0f;

    return true;
}

// ......����δ֪
bool CGfxOpenGL::Shutdown()
{
    return true;
}

void CGfxOpenGL::SetupProjection(int width, int height)
{
    // ���ڸ߶�ǿ�Ʋ�Ϊ0
    if ( 0 == height )
    {
        height = 1;
    }

    // �Ӵ��任�����������ɼ�����
    glViewport(0, 0, width, height);

    // ���ò���ʼ��ͶӰ����
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // �����ӽǴ�С�����ڿ�߱ȣ�ǰ����ʾ����
    gluPerspective(52.0f, (GLdouble)width / (GLdouble)height, 1.0f, 1000.0f);

    // ���ò���ʼ��ģ�;���
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    m_windowWidth = width;
    m_windowHeight = height;
}

void CGfxOpenGL::Prepare(float dt)
{
    // �𽥸ı�ģ����ת�Ƕ�
    m_angle += 0.1f;
}

void CGfxOpenGL::Render()
{
    // �����ɫ����Ȼ�����
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // ����ģ���ƶ�λ������ת�Ƕ�
    glTranslated(0.0f, 0.0f, -5.0f);        // ����ģ����ʾ��δ֪
    glRotatef(m_angle, 1.0f, 0.0f, 0.0f);   // ����ģ����x���ϵĽǶȷ���
    glRotatef(m_angle, 0.0f, 1.0f, 0.0f);   // ����ģ����y���ϵĽǶȷ���
    glRotatef(m_angle, 0.0f, 0.0f, 1.0f);   // ����ģ����z���ϵĽǶȷ���

    // ����ǰ��ɫ
    glColor3f(0.7f, 1.0f, 0.3f);

    // ����������
    glBegin(GL_TRIANGLES);
        glVertex3f(1.0f, -1.0f, 0.0f);
        glVertex3f(-1.0f, -1.0f, 0.0f);
        glVertex3f(0.0f, 1.0f, 0.0f);
    glEnd();
}
