#include "3D_Function.h"

#include <windows.h>
#include <gl/GL.H>
#include <gl/GLU.H>
#include <gl/GLAUX.H>

#include "MD5.h"


extern MD5_Model_t  *md5File;
extern MD5_Anim_t   *md5anim;

float rotate_angle = 0.0f;
int index = 0;

// �ٶ���һ��Ĭ�ϵĹ�Դ
static float ambient[]          = {1.0f, 1.0f, 1.0f, 1.0f};
static float diffuseLight[]     = {1.0f, 1.0f, 1.0f, 1.0f};
static float specularLight[]    = {1.0f, 1.0f, 1.0f, 1.0f};
static float lightPosition[]    = {0.0f, 5.0f, 5.0f, 0.0f};


void InitOpenGL()
{
    glClearColor(0.0f, 0.0f, 1.0f, 0.5f);
    glClearDepth(1.0f);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);

    glShadeModel(GL_SMOOTH);
    glDepthFunc(GL_LEQUAL);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    // ����0�Ź�Դ
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    if ( !glIsEnabled(GL_LIGHTING) )
    {
        glEnable(GL_LIGHTING);
    }

    if ( !glIsEnabled(GL_LIGHT0) )
    {
        glEnable(GL_LIGHT0);
    }

    if ( !glIsEnabled(GL_POLYGON_SMOOTH) )
    {
        glEnable(GL_POLYGON_SMOOTH);
    }
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
	// �û��Զ���Ļ��ƹ���
	// �����������ֵ
    GLfloat no_mat[]            = {0.0f, 0.0f, 0.0f, 1.0f}; // �޲�����ɫ
    GLfloat mat_ambient[]       = {0.7f, 0.7f, 0.7f, 1.0f}; // ������ɫ
    GLfloat mat_ambient_color[] = {0.8f, 0.6f, 0.2f, 1.0f};
    GLfloat mat_diffuse[]       = {0.2f, 0.5f, 0.8f, 1.0f}; // ɢ����ɫ
    GLfloat mat_specular[]      = {1.0f, 1.0f, 1.0f, 1.0f}; // ���淴����ɫ
    GLfloat no_shininess[]      = {0.0f};                   // ���淴��ָ��Ϊ0
    GLfloat low_shininess[]     = {5.0f};                   // ���淴��ָ��Ϊ5
    GLfloat high_shininess[]    = {100.0f};                 // ���淴��ָ��Ϊ100
    GLfloat mat_emission[]      = {0.3f, 0.2f, 0.3f, 0.0f}; // �������ɫ


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0f, -45.0f, -250.0f);
    
    glRotatef(-60.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(-10.0f, 0.0f, 0.0f, 1.0f);
    glRotatef(rotate_angle, 0.0f, 0.0f, 1.0f);

    DrawAnim(md5File, md5anim, index);

    rotate_angle += 0.5f;

    if ( index < md5anim->num_frames - 1 )
    {
        index++;
    }
    else
    {
        index = 0;
    }
}
