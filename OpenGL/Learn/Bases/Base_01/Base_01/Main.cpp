#include <gl\GLUT.H>
#include <stdio.h>


void Initialize();
void MouseHandler(int button, int state, int x, int y);
void KeyboardHandler(unsigned char key, int x, int y);
void MainMenuHandler(int option);
void Animate();
void Reshape(int width, int height);
void Display();


int main(int argc, char **argv)
{
    // ��ʼ��GULT�⣬���ʹ��ڳ���ͨ��
    glutInit(&argc, argv);
    
    // ���ó�ʼ��ʾģʽ
    //      GLUT_RGB            ָ��RGB��ɫģʽ�Ĵ���
    //      GLUT_RGBA           ָ��RGBA��ɫģʽ�Ĵ���
    //      GLUT_INDEX          ָ����ɫ����ģʽ�Ĵ���
    //      GLUT_SINGLE         ָ�������洰��
    //      GLUT_DOUBLE         ָ��˫���洰��
    //      GLUT_ACCUM          ����ʹ���ۼӻ���
    //      GLUT_ALPHA          ���ڵ���ɫ��������alphaֵ
    //      GLUT_DEPTH          ����ʹ����Ȼ���
    //      GLUT_STENCIL        ����ʹ��ģ�建��
    //      GLUT_MULTISAMPLE    ָ��֧�ֶ��������ܵĴ���
    //      GLUT_STEREO         ָ�����崰��
    //      GLUT_LUMINANCE      ����ʹ��������ɫģ��
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    // �������ڣ��������ϵ�λ�ã���ߣ����⣩
    glutInitWindowPosition(100, 150);
    glutInitWindowSize(1024, 768);
    glutCreateWindow("BOGLGP Chapter 1");

    // ��ʼ��
    Initialize();

    // ע��ص�����
    glutDisplayFunc(Display);           // ע���ͼ����
    glutReshapeFunc(Reshape);           // ע�ᴰ�ڱ仯���ú���
    glutMouseFunc(MouseHandler);        // ע������¼�
    glutKeyboardFunc(KeyboardHandler);  // ע������¼�
    glutIdleFunc(Animate);              // ע����Ͼʱִ�к���

    glutMainLoop();                     // ��ѭ�� ���˳�

    return 0;
}


/***********************************************************************
��ʼ��
    ����ʱ���ã������˵���������Դ��������Ⱦģ�͡������ɫ����������
************************************************************************/
void Initialize()
{
    //  �����˵������ز˵����
    int mainMenu;
    mainMenu = glutCreateMenu(MainMenuHandler);

    // �Ҽ��˵����"Exit"ѡ��
    glutSetMenu(mainMenu);
    glutAddMenuEntry("Exit", 0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    // ����������Ȼ���������
    glEnable(GL_DEPTH_TEST);
}

/***********************************************************************
�������¼�
************************************************************************/
void MouseHandler(int button, int state, int x, int y)
{
    printf("---------/tMouseHandler\t%d\n", button);

    switch ( button )
    {
        // Ϊ����������˳��¼�
        case GLUT_LEFT_BUTTON:
        {
            exit(0);
        } break;

        default:
            break;
    }

    // �ػ���Ļ
    glutPostRedisplay();
}

/***********************************************************************
��Ӽ����¼�
************************************************************************/
void KeyboardHandler(unsigned char key, int x, int y)
{
    printf("---------/tKeyboardHandler\t%c\n", key);

    switch ( key )
    {
        // �����ϵ�q������˳��¼�
        case 'q':
        {
            exit(0);
        } break;

        default:
            break;
    }

    glutPostRedisplay();
}

/***********************************************************************
�˵��ص��¼�
......������������ò����
************************************************************************/
void MainMenuHandler(int option)
{
    printf("---------/tMainMenuHandler\t%d\n", option);

    switch ( option )
    {
        case 0:
        {
            exit(0);
        } break;

        default:
            break;
    }

    glutPostRedisplay();
}

void Animate()
{
    //printf("......................Animate\n");

    glutPostRedisplay();
}

/**********************************************************************
���ڱ仯ʱ���»���
***********************************************************************/
void Reshape(int width, int height)
{
    printf("---------/tReshape\t%d\t%d\n", width, height);

    if (0 == height)
    {
        return;
    }

    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0f, width / height, 1.0f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
}

/***********************************************************************
��ͼ����
************************************************************************/
void Display()
{
    //printf("---------/tDisplay\n");

    // ��ʼ���۲����
    glLoadIdentity();

    // ���þ�ͷλ�ã���ͷ���򣬾�ͷ��λ
    gluLookAt(0.0f, 1.0f, 6.0f,
              0.0f, 0.0f, 0.0f,
              0.0f, 1.0f, 0.0f);

    // �����Ļ
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // ����һ��������
    // ����ָ��3��������ɫ��λ�ã�opengl��
    glBegin(GL_TRIANGLES);
        glColor3f(10.0f, 0.0f, 0.0f);
        glVertex3f(2.0f, 2.5f, -1.0f);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-3.5f, -2.5f, -1.0f);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(2.0f, -4.0f, 0.0f);
    glEnd();

    // ���ƶ����
    // ����ָ��5��������ɫ��λ��
    glBegin(GL_POLYGON);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(-1.0f, 2.0f, 0.0f);
        glColor3f(1.0f, 1.0f, 0.0f);
        glVertex3f(-3.0f, -0.5f, 0.0f);
        glColor3f(0.0f, 1.0f, 1.0f);
        glVertex3f(-1.5f, -3.0f, 0.0f);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex3f(1.0f, -2.0f, 0.0f);
        glColor3f(1.0f, 0.0f, 1.0f);
        glVertex3f(1.0f, 1.0f, 0.0f);
    glEnd();

    // ��������
    glutSwapBuffers();
}

