#include <gl/glut.h>

void myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glRectf(-0.5f, 0.5f, 0.5f, 0.5f);
	glFlush();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("��һ��OpengL����");
	glutDisplayFunc(&myDisplay);
	glutMainLoop();

	return 0;
}
