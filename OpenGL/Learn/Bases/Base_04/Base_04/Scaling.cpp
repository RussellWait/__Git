#include "Scaling.h"


bool Scaling::Init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    m_scaleFactor = 1.0f;
    m_increaseScale = true;

    return true;
}

void Scaling::Prepare(float dt)
{
    if ( m_increaseScale )
    {
        m_scaleFactor += 0.001f;
    }
    else
    {
        m_scaleFactor -= 0.001f;
    }

    if ( m_scaleFactor > 2.0f )
    {
        m_increaseScale = false;
    }
    else if ( m_scaleFactor <= 0.1f )
    {
        m_increaseScale = true;
    }
}

void Scaling::Render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -10.0f);
    glRotated(90.0f, 1.0f, 0.0f, 0.0f);
    glScalef(m_scaleFactor, m_scaleFactor, m_scaleFactor);

    DrawPlane();
}

void Scaling::DrawPlane()
{
    glBegin(GL_TRIANGLE_STRIP);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(-2.0f, 0.0f, -2.0f);
        glColor3f(0.0f, 1.f, 0.0f);
        glVertex3f(2.0f, 0.0f, -2.0f);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(-2.0f, 0.0f, 2.0f);
        glColor3f(1.0f, 1.0f, 0.0f);
        glVertex3f(2.0f, 0.0f, 2.0f);
    glEnd();
}
