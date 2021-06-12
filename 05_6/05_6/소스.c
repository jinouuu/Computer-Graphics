#include<GL/glut.h>
#include<stdlib.h>

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glColor3f(1.0, 0.0, 0.0);
	glutWireCube(1.0);

	glPushMatrix();

	glColor3f(0.0, 1.0, 0.0);
	glTranslatef(-1.5, 0.0, 1.5);
	glutWireCube(1.0);

	glPopMatrix();

	glColor3f(0.0, 0.0, 1.0);
	glTranslatef(1.5, 0.0, 1.5);
	glutWireCube(1.0);

	glFlush();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
	//glOrtho(-7.0, 7.0, -7.0, 7.0, 1.5, 20.0);
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("투영 방법 예제");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
}