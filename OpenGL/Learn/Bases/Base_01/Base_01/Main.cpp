#include <gl\GLUT.H>


void Initialize();
void MouseHandler(int button, int state, int x, int y);
void KeyboardHandler(unsigned char key, int x, int y);
void MainMenuHandler(int option);
void Animate();
void Reshape(int width, int height);
void Display();


int main(int argc, char **argv)
{
    // ���û�����Ϣ
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    // ��������
    glutInitWindowPosition(100, 150);
    glutInitWindowSize(1024, 768);
    glutCreateWindow("BOGLGP Chapter 1");

    Initialize();

    // ע��ص�����
    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    glutMouseFunc(MouseHandler);
    glutKeyboardFunc(KeyboardHandler);
    glutIdleFunc(Animate);

    glutMainLoop();

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

    glEnable(GL_DEPTH_TEST);
}

/***********************************************************************
�������¼�
************************************************************************/
void MouseHandler(int button, int state, int x, int y)
{
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
************************************************************************/
void MainMenuHandler(int option)
{
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
    glutPostRedisplay();
}

/**********************************************************************
���ڱ仯ʱ���»���
***********************************************************************/
void Reshape(int width, int height)
{
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
������ݲ�����
************************************************************************/
void Display()
{
    // ���þ�ͷ
    glLoadIdentity();
    gluLookAt(0.0f, 1.0f, 6.0f,
              0.0f, 0.0f, 0.0f,
              0.0f, 1.0f, 0.0f);

    // �����Ļ
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // ����һ��������
    glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(2.0f, 2.5f, -1.0f);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-3.5f, -2.5f, -1.0f);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(2.0f, -4.0f, 0.0f);
    glEnd();

    // ���ƶ����
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

