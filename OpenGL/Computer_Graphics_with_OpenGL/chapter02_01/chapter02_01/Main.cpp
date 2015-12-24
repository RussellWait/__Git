#include <GL/glut.h>

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 2000.0, 0.0, 1500.0);
}

void lineSegment(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
        glVertex2i(1800, 150);
        glVertex2i(100, 1450);
    glEnd();

    glFlush();
}

void main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 100);
    glutInitWindowSize(400, 800);
    glutCreateWindow("An Example OpenGL Program");

    init();
    glutDisplayFunc(lineSegment);
    glutMainLoop();
}
