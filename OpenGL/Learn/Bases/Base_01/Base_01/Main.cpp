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
    // 设置基本信息
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    // 创建窗口
    glutInitWindowPosition(100, 150);
    glutInitWindowSize(1024, 768);
    glutCreateWindow("BOGLGP Chapter 1");

    Initialize();

    // 注册回调函数
    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    glutMouseFunc(MouseHandler);
    glutKeyboardFunc(KeyboardHandler);
    glutIdleFunc(Animate);

    glutMainLoop();

    return 0;
}


/***********************************************************************
初始化
    启动时调用：创建菜单、创建光源、设置渲染模型、清除颜色、加载纹理
************************************************************************/
void Initialize()
{
    //  创建菜单，返回菜单句柄
    int mainMenu;
    mainMenu = glutCreateMenu(MainMenuHandler);

    // 右键菜单添加"Exit"选项
    glutSetMenu(mainMenu);
    glutAddMenuEntry("Exit", 0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glEnable(GL_DEPTH_TEST);
}

/***********************************************************************
添加鼠标事件
************************************************************************/
void MouseHandler(int button, int state, int x, int y)
{
    switch ( button )
    {
        // 为鼠标左键添加退出事件
        case GLUT_LEFT_BUTTON:
        {
            exit(0);
        } break;

        default:
            break;
    }

    // 重绘屏幕
    glutPostRedisplay();
}

/***********************************************************************
添加键盘事件
************************************************************************/
void KeyboardHandler(unsigned char key, int x, int y)
{
    switch ( key )
    {
        // 键盘上的q键添加退出事件
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
菜单回调事件
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
窗口变化时重新绘制
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
清空内容并绘制
************************************************************************/
void Display()
{
    // 设置镜头
    glLoadIdentity();
    gluLookAt(0.0f, 1.0f, 6.0f,
              0.0f, 0.0f, 0.0f,
              0.0f, 1.0f, 0.0f);

    // 清空屏幕
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 绘制一个三角形
    glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(2.0f, 2.5f, -1.0f);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-3.5f, -2.5f, -1.0f);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(2.0f, -4.0f, 0.0f);
    glEnd();

    // 绘制多边形
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

    // 交换缓存
    glutSwapBuffers();
}

