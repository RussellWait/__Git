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

// 初始化opengl
bool CGfxOpenGL::Init()
{
    // 设置背景色 和 模型初始角度
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    m_angle = 0.0f;

    return true;
}

// ......作用未知
bool CGfxOpenGL::Shutdown()
{
    return true;
}

void CGfxOpenGL::SetupProjection(int width, int height)
{
    // 窗口高度强制不为0
    if ( 0 == height )
    {
        height = 1;
    }

    // 视窗变换函数，决定可见区域
    glViewport(0, 0, width, height);

    // 设置并初始化投影矩阵
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // 设置视角大小，窗口宽高比，前后显示界限
    gluPerspective(52.0f, (GLdouble)width / (GLdouble)height, 1.0f, 1000.0f);

    // 设置并初始化模型矩阵
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    m_windowWidth = width;
    m_windowHeight = height;
}

void CGfxOpenGL::Prepare(float dt)
{
    // 逐渐改变模型旋转角度
    m_angle += 0.1f;
}

void CGfxOpenGL::Render()
{
    // 清除颜色和深度缓冲区
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // 设置模型移动位置与旋转角度
    glTranslated(0.0f, 0.0f, -5.0f);        // 设置模型显示的未知
    glRotatef(m_angle, 1.0f, 0.0f, 0.0f);   // 设置模型在x轴上的角度分量
    glRotatef(m_angle, 0.0f, 1.0f, 0.0f);   // 设置模型在y轴上的角度分量
    glRotatef(m_angle, 0.0f, 0.0f, 1.0f);   // 设置模型在z轴上的角度分量

    // 设置前景色
    glColor3f(0.7f, 1.0f, 0.3f);

    // 绘制三角形
    glBegin(GL_TRIANGLES);
        glVertex3f(1.0f, -1.0f, 0.0f);
        glVertex3f(-1.0f, -1.0f, 0.0f);
        glVertex3f(0.0f, 1.0f, 0.0f);
    glEnd();
}
