#include "3D_Function.h"

#include <windows.h>
#include <gl/GL.H>
#include <gl/GLU.H>
#include <gl/GLAUX.H>

#include "MD5.h"


extern MD5_Model_t *md5File;
float rotate_angle = 0.0f;


void InitOpenGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
    glClearDepth(1.0f);

    glEnable(GL_DEPTH_TEST);

    glShadeModel(GL_SMOOTH);
    glDepthFunc(GL_LEQUAL);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void SetupMatrices(int w, int h)
{
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLdouble)w / (GLdouble)h, 0.01f, 1000.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslated(0.0f, -55.0f, -250.0f);
    
    //glRotatef(-60.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(rotate_angle, 0.0f, 0.0f, 1.0f);
    rotate_angle += 0.1f;

    glBegin(GL_LINE);
		DrawModel(md5File);
    glEnd();
}
