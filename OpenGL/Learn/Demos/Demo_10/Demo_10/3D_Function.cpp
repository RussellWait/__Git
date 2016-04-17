#include "3D_Function.h"

#include <windows.h>
#include <gl/GL.H>
#include <gl/GLU.H>
#include <gl/GLAUX.H>


GLuint      textures[1];
GLfloat     dist = 0.0f;


void InitOpenGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
    glClearDepth(1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void SetupMatrices(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLdouble)w / (GLdouble)h, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glTranslatef(0, 0, dist);
    gluLookAt(0.0f, 0.0f, 0.0f,
              0.0f, 0.0f, -1.0f,
              0.0f, 1.0f, 0.0f);

    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glBegin(GL_QUADS);
    glTexCoord2d(0.0f, 0.0f);
    glVertex3d(-1.0f, -1.0f, 0.0f);
    glTexCoord2d(1.0f, 0.0f);
    glVertex3d(1.0f, -1.0f, 0.0f);
    glTexCoord2d(1.0f, 1.0f);
    glVertex3d(1.0f, 1.0f, 0.0f);
    glTexCoord2d(0.0f, 1.0f);
    glVertex3d(-1.0f, 1.0f, 0.0f);
    glEnd();
    
    dist -= 0.5f;
}


int LoadTextures(char *fileName)
{
    int state = FALSE;

    AUX_RGBImageRec *textureImg[1];
    if (textureImg[0] = auxDIBImageLoad(fileName))
    {
        state = TRUE;

        glGenTextures(1, textures);
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, textureImg[0]->sizeX, textureImg[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, textureImg[0]->data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINES);
        gluBuild2DMipmaps(GL_TEXTURE_2D, 3, 256, 256, GL_RGB, GL_UNSIGNED_BYTE, textureImg[0]->data);

        if (textureImg[0])
        {
            if (textureImg[0]->data)
            {
                free(textureImg[0]->data);
            }
            free(textureImg[0]);
        }
    }

    return state;
}
