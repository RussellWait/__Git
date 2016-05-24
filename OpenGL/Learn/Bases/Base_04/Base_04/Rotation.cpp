#include "Rotation.h"


bool Rotation::Init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glPolygonMode(GL_BACK, GL_LINE);

    m_xAxisAngle = 0.0f;
    m_yAxisAngle = 0.0f;

    return true;
}

void Rotation::Prepare(float dt)
{
    m_xAxisAngle += 0.05f;
    m_yAxisAngle += 0.25f;

    if ( m_xAxisAngle >= 360.0f )
    {
        m_xAxisAngle = 0.0f;
    }

    if ( m_yAxisAngle >= 360.0f )
    {
        m_yAxisAngle = 0.0f;
    }
}

void Rotation::Render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    
    glTranslatef(0.0f, 0.0f, -10.0f);
    DrawAxes();

    glRotatef(m_xAxisAngle, 1.0f, 0.0f, 0.0f);
    glRotatef(m_yAxisAngle, 0.0f, 1.0f, 0.0f);
    DrawPlane();
}

void Rotation::DrawPlane()
{
    // 绘制平面
    glBegin(GL_TRIANGLE_STRIP);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(-2.0f, 0.0f, -2.0f);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(2.0f, 0.0f, -2.0f);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(-2.0f, 0.0f, 2.0f);
        glColor3f(1.0f, 1.0f, 0.0f);
        glVertex3f(2.0f, 0.0f, 2.0f);
    glEnd();

    // 垂直于平面的发向量
    glBegin(GL_LINES);
        glColor3f(1.0f, 1.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 3.0f, 0.0f);
    glEnd();

    // 一条沿平面的切向量
    glBegin(GL_LINES);
        glColor3f(1.0f, 1.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(3.0f, 0.0f, 0.0f);
    glEnd();
}

void Rotation::DrawAxes()
{
    // x轴
    glBegin(GL_LINES);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(3.0f, 0.0f, 0.0f);
    glEnd();

    // y轴
    glBegin(GL_LINES);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 3.0f, 0.0f);
    glEnd();
}
