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
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);		// 设置背景色

    return true;
}

bool CGfxOpenGL::Shutdown()
{
    return true;
}

// 设置窗口宽高
void CGfxOpenGL::SetupProjection(int width, int height)
{
    // 窗口高度至少为1
    if ( 0 == height )
    {
        height = 1;
    }

    // 窗口位置与大小
    glViewport(0, 0, width, height);

    // 投影矩阵
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // 设置视角大小，窗口宽高比，前后显示界限
    gluPerspective(52.0f, (GLfloat)width / (GLdouble)height, 1.0f, 1000.0f);

    // 设置为模型矩阵并初始化
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
