#include<GL/glut.h>
#include<GL/GL.H>
#include<stdlib.h>

static GLfloat spin = 0.0;

void display()
{
	int r, g, b;
	r = rand() % 256;
	g = rand() % 256;
	b = rand() % 256;

	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();
	glRotatef(spin, 0.0, 0.0, 1.0);
	glColor3f((GLfloat)r / 255, (GLfloat)g / 255, (GLfloat)b / 255);
	glRectf(-25.0, -25.0, 25.0, 25.0);
	glPopMatrix();

	glutSwapBuffers();
}

void spinDisplay()
{
	spin = spin + 0.01;
	if (spin > 360.0)
		spin = spin - 360.0;
	glutPostRedisplay();
}

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-50.0, 50.0, -50.0,50.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void mouse(int button, int state, int x, int y)
{
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)	glutIdleFunc(spinDisplay);
		break;

	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN) glutIdleFunc(NULL);
		break;

	default:
		break;
	}
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(250, 250);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("02_5 �簢�� ȸ��");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMainLoop();
}