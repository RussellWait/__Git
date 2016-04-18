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

bool CGfxOpenGL::Init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    m_angle = 0.0f;

    return true;
}

// 
bool CGfxOpenGL::Shutdown()
{
    return true;
}

void CGfxOpenGL::SetupProjection(int width, int height)
{
    if ( 0 == height )
    {
        height = 1;
    }

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(52.0f, (GLdouble)width / (GLdouble)height, 1.0f, 1000.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    m_windowWidth = width;
    m_windowHeight = height;
}

void CGfxOpenGL::Prepare(float dt)
{
    m_angle += 0.1f;
}

void CGfxOpenGL::Render()
{
    // 清除颜色和深度缓冲区
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // 设置移动位置与旋转角度
    glTranslated(0.0f, 0.0f, -5.0f);
    glRotatef(m_angle, 1.0f, 0.0f, 0.0f);
    glRotatef(m_angle, 0.0f, 1.0f, 0.0f);
    glRotatef(m_angle, 0.0f, 0.0f, 1.0f);

    // 设置前景色
    glColor3f(0.7f, 1.0f, 0.3f);

    // 绘制三角形
    glBegin(GL_TRIANGLES);
        glVertex3f(1.0f, -1.0f, 0.0f);
        glVertex3f(-1.0f, -1.0f, 0.0f);
        glVertex3f(0.0f, 1.0f, 0.0f);
    glEnd();
}
