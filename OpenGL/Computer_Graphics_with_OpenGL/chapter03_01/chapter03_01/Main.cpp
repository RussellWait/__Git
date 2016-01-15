#include <GL/glut.h>
#include <iostream>

GLsizei winWidth = 600, winHeight = 500;
GLint xRaster = 25, yRaster = 150;

GLubyte label[36] = 
{
    'J', 'a', 'n',      'F', 'e', 'b',      'M', 'a', 'r',
    'A', 'p', 'r',      'M', 'a', 'y',      'J', 'u', 'n',
    'J', 'u', 'l',      'A', 'u', 'g',      'S', 'e', 'p',
    'O', 'c', 't',      'N', 'o', 'v',      'D', 'e', 'c'
};

GLint datraValue[12] = {420, 342, 324, 310, 262, 185, 190, 196, 217, 240, 312, 438};

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 600.0, 0.0, 500.0);
}

// ’€œﬂÕº
void lineGraph(void)
{
    GLint x = 30;

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINE_STRIP);
        for (GLint month = 0; month < 12; month++)
        {
            glVertex2i(x + month*50, datraValue[month]);
        }
    glEnd();

    glColor3f(1.0, 0.0, 0.0);
    for (GLint month = 0; month < 12; month++)
    {
        glRasterPos2i(xRaster + month*50, datraValue[month] - 4);
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '*');
    }

    glColor3f(0.0, 0.0, 0.0);
    xRaster = 20;
    for (GLint month = 0; month < 12; month++)
    {
        glRasterPos2d(xRaster, yRaster);
        for (GLint k = 3*month; k < 3*month + 3; k++)
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, label[k]);
        }
        xRaster += 50;
    }
    glFlush();
}

// ÷±∑ΩÕº
void barChart(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 0.0, 0.0);
    for (GLint month = 0; month < 12; month++)
    {
        glRecti(20 + month*50, 165, 40 + month*50, datraValue[month]);
    }

    glColor3f(0.0, 0.0, 0.0);
    xRaster = 20;
    for (GLint month = 0; month < 12; month++)
    {
        glRasterPos2i(xRaster, yRaster);
        for (GLint k = 3*month; k < 3*month+3; k++)
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, label[k]);
        }
        xRaster += 50;
    }
    glFlush();
}

void winReshapeFcn(GLint newWidth, GLint newHeight)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, GLdouble(newWidth), 0.0, GLdouble(newHeight));
    glClear(GL_COLOR_BUFFER_BIT);
}

void main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("Line Chart Data Plot");

    init();
    glutDisplayFunc(lineGraph);
    //glutDisplayFunc(barChart);
    glutReshapeFunc(winReshapeFcn);
    glutMainLoop();
}
