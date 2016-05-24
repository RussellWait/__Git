#include "Projections.h"

#pragma warning(disable:4305)


bool Projections::Init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    return true;
}

void Projections::SetupProjection(int width, int height)
{
    if ( 0 == height )
    {
        height = 1;
    }

    glViewport(0, 0, width, height);

    UpdateProjection(false);
}

void Projections::Render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glLoadIdentity();

    glTranslatef(0.4f, 0.0f, -1.5f);
    glRotatef(15.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(30.0f, 0.0f, 1.0f, 0.0f);
    glScaled(0.75f, 0.75f, 0.75f);
    DrawCube(0.0f, 0.0f, 0.0f);
}

void Projections::DrawCube(float xPos, float yPos, float zPos)
{
    glPushMatrix();
        glTranslatef(xPos, yPos, zPos);
        glBegin(GL_QUADS);
            glVertex3f(0.0f, 0.0f, 0.0f);       // top face
            glVertex3f(0.0f, 0.0f, -1.0f);
            glVertex3f(-1.0f, 0.0f, -1.0f);
            glVertex3f(-1.f, 0.0f, 0.0f);

            glVertex3f(0.0f, 0.0f, 0.0f);       // front face
            glVertex3f(-1.0f, 0.0f, 0.0f);
            glVertex3f(-1.0f, -1.0f, 0.0f);
            glVertex3f(0.0f, -1.0f, 0.0f);

            glVertex3f(0.0f, 0.0f, 0.0f);       // right face
            glVertex3f(0.0f, -1.0f, 0.0f);
            glVertex3f(0.0f, -1.0f, -1.0f);
            glVertex3f(0.0f, 0.0f, -1.0f);

            glVertex3f(-1.0f, 0.0f, 0.0f);      // left face
            glVertex3f(-1.0f, 0.0f, -1.0f);
            glVertex3f(-1.0f, -1.0f, -1.0f);
            glVertex3f(-1.0f, -1.0f, 0.0f);

            glVertex3f(0.0f, -1.0f, 0.0f);      // bottom face
            glVertex3f(0.0f, -1.0f, -1.0f);
            glVertex3f(-1.0f, -1.0f, - 1.0f);
            glVertex3f(-1.0f, -1.0f, 0.0f);

            glVertex3f(0.0f, 0.0f, -1.0f);      // back face
            glVertex3f(-1.0f, 0.0f, -1.0f);
            glVertex3f(-1.0f, -1.0f, -1.0f);
            glVertex3f(0.0f, -1.0f, -1.0f);
        glEnd();
    glPopMatrix();
}

void Projections::UpdateProjection(bool toggle /* = FALSE */)
{
    static bool usePerspective = true;

    if ( toggle )
    {
        usePerspective = !usePerspective;
    }

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if ( usePerspective )
    {
        glFrustum(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1000.0f);
    }
    else
    {
        glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1000.0f);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
