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
    glEnable(GL_AUTO_NORMAL);       // 执行后，图形能把光反射到各个方向
    glEnable(GL_NORMALIZE);         // 根据函数glNormal的设置条件，启用法向量

    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
    glClearDepth(1.0f);

    glShadeModel(GL_SMOOTH);        // 设置着色模式
                                    //      GL_SMOOTH   平滑着色（默认）
                                    //      GL_FLAT     恒定着色

    glDepthFunc(GL_LEQUAL);         // 指定深度缓冲比函数
                                    //      GL_NEVER    不通过
                                    //      GL_ALWAYS   总通过
                                    //      GL_LESS     如果输入的深度值小于参考值，则通过
                                    //      GL_LEQUAL   如果输入的深度值小于等于参考值，则通过
                                    //      GL_GREATER  如果输入的深度值大于参考值，则通过
                                    //      GL_GEQUAL   如果输入的深度值大于等于参考值，则通过
                                    //      GL_EQUAL    如果输入的深度值等于参考值，则通过
                                    //      GL_NOTEQUAL 如果输入的深度值不等于参考值，则通过

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void SetupMatrices(int w, int h)
{
    // 设置窗口位置及其大小
    glViewport(0, 0, w, h);

    // 设置模型矩阵
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.05, (GLdouble)w / (GLdouble)h, 0.1f, 1000.0f);

    // 设置观察矩阵
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
