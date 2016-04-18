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
    // 初始化GULT库，并和窗口程序通信
    glutInit(&argc, argv);
    
    // 设置初始显示模式
    //      GLUT_RGB            指定RGB颜色模式的窗口
    //      GLUT_RGBA           指定RGBA颜色模式的窗口
    //      GLUT_INDEX          指定颜色索引模式的窗口
    //      GLUT_SINGLE         指定单缓存窗口
    //      GLUT_DOUBLE         指定双缓存窗口
    //      GLUT_ACCUM          窗口使用累加缓存
    //      GLUT_ALPHA          窗口的颜色分量包含alpha值
    //      GLUT_DEPTH          窗口使用深度缓存
    //      GLUT_STENCIL        窗口使用模板缓存
    //      GLUT_MULTISAMPLE    指定支持多样本功能的窗口
    //      GLUT_STEREO         指定立体窗口
    //      GLUT_LUMINANCE      窗口使用亮度颜色模型
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    // 创建窗口（窗口左上点位置，宽高，标题）
    glutInitWindowPosition(100, 150);
    glutInitWindowSize(1024, 768);
    glutCreateWindow("BOGLGP Chapter 1");

    // 初始化
    Initialize();

    // 注册回调函数
    glutDisplayFunc(Display);           // 注册绘图函数
    glutReshapeFunc(Reshape);           // 注册窗口变化调用函数
    glutMouseFunc(MouseHandler);        // 注册鼠标事件
    glutKeyboardFunc(KeyboardHandler);  // 注册键盘事件
    glutIdleFunc(Animate);              // 注册闲暇时执行函数

    glutMainLoop();                     // 主循环 不退出

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

    // 开启更新深度缓冲区功能
    glEnable(GL_DEPTH_TEST);
}

/***********************************************************************
添加鼠标事件
************************************************************************/
void MouseHandler(int button, int state, int x, int y)
{
    printf("---------/tMouseHandler\t%d\n", button);

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
    printf("---------/tKeyboardHandler\t%c\n", key);

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
......这个函数的作用不清楚
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
窗口变化时重新绘制
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
绘图函数
************************************************************************/
void Display()
{
    //printf("---------/tDisplay\n");

    // 初始化观察矩阵
    glLoadIdentity();

    // 设置镜头位置，镜头方向，镜头方位
    gluLookAt(0.0f, 1.0f, 6.0f,
              0.0f, 0.0f, 0.0f,
              0.0f, 1.0f, 0.0f);

    // 清空屏幕
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 绘制一个三角形
    // 依次指定3个顶点颜色和位置（opengl）
    glBegin(GL_TRIANGLES);
        glColor3f(10.0f, 0.0f, 0.0f);
        glVertex3f(2.0f, 2.5f, -1.0f);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-3.5f, -2.5f, -1.0f);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(2.0f, -4.0f, 0.0f);
    glEnd();

    // 绘制多边形
    // 依次指定5个顶点颜色和位置
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

