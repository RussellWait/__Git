#include "3D_Function.h"

#include <windows.h>
#include <gl/GL.H>
#include <gl/GLU.H>
#include <gl/GLAUX.H>
#include "MD3.h"


extern CMD3 g_MD3_1;
extern CMD3 g_MD3_2;
extern CMD3 g_MD3_3;


void InitOpenGL()
{
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_AUTO_NORMAL);       // ִ�к�ͼ���ܰѹⷴ�䵽��������
    glEnable(GL_NORMALIZE);         // ���ݺ���glNormal���������������÷�����

    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
    glClearDepth(1.0f);

    glShadeModel(GL_SMOOTH);        // ������ɫģʽ
                                    //      GL_SMOOTH   ƽ����ɫ��Ĭ�ϣ�
                                    //      GL_FLAT     �㶨��ɫ

    glDepthFunc(GL_LEQUAL);         // ָ����Ȼ���Ⱥ���
                                    //      GL_NEVER    ��ͨ��
                                    //      GL_ALWAYS   ��ͨ��
                                    //      GL_LESS     �����������ֵС�ڲο�ֵ����ͨ��
                                    //      GL_LEQUAL   �����������ֵС�ڵ��ڲο�ֵ����ͨ��
                                    //      GL_GREATER  �����������ֵ���ڲο�ֵ����ͨ��
                                    //      GL_GEQUAL   �����������ֵ���ڵ��ڲο�ֵ����ͨ��
                                    //      GL_EQUAL    �����������ֵ���ڲο�ֵ����ͨ��
                                    //      GL_NOTEQUAL �����������ֵ�����ڲο�ֵ����ͨ��

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void SetupMatrices(int w, int h)
{
    // ���ô���λ�ü����С
    glViewport(0, 0, w, h);

    // ����ģ�;���
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.05, (GLdouble)w / (GLdouble)h, 0.1f, 1000.0f);

    // ���ù۲����
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0f, -5.0f, -90.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);

    g_MD3_1.Animate(0, 200, 10);
    g_MD3_2.Animate(0, 200, 10);
    g_MD3_3.Animate(0, 200, 10);

    g_MD3_1.Attach(&g_MD3_2, 0);
    g_MD3_2.Attach(&g_MD3_3, 0);
    g_MD3_1.RenderT();
}
