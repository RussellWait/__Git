#include "Translation.h"


bool Translation::Init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    m_zPos = 0.0f;
    m_direction = true;

    return true;
}

void Translation::Prepare(float dt)
{
    if ( m_direction )
    {
        m_zPos -= 0.01f;
    }
    else
    {
        m_zPos += 0.01f;
    }

    if ( m_zPos >= 0.0f )
    {
        m_direction = true;
    }
    else if ( m_zPos < -20.0f)
    {
        m_direction = false;
    }
}

void Translation::Render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslated(0.0f, 0.0f, m_zPos);

    DrawPlane();
}

void Translation::DrawPlane()
{
    glBegin(GL_TRIANGLE_STRIP);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(-2.0f, -2.0f, -2.0f);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(2.0f, -2.0f, -2.0f);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(-2.0f, -2.0f, 2.0f);
        glColor3f(1.0f, 1.0f, 0.0f);
        glVertex3f(2.0f, -2.0f, 2.0f);
    glEnd();
}
