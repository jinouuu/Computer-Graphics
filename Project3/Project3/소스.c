#include<GL/glut.h>
#include<stdlib.h>
#include<stdio.h>

static GLfloat spin = 0.0;

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
}

void triangle(void)
{
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(-0.5, -0.5);
	glColor3f(0.0, 1.0, 0.0);
	glVertex2f(0.5, -0.5);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(-0.5, 0.5);
	glEnd();
}

void spinDisplay()
{
	spin = spin + 0.1;
	if (spin > 360.0)
		spin = spin - 360.0;
	glutPostRedisplay();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glRotatef(spin, 0.0, 0.0, 1.0);
	triangle();
	glPopMatrix();
	glutSwapBuffers();
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		glutIdleFunc(spinDisplay);
	}
}

void reshape(int new_w, int new_h)
{
	glViewport(0, 0, new_w, new_h);
	float WidthFactor = (float)new_w / 300.0;
	float HeightFactor = (float)new_h / 300.0;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(-1.0 * WidthFactor, 1.0 * WidthFactor, -1.0 * HeightFactor, 1.0 * HeightFactor);
	printf("%lf %lf", WidthFactor, HeightFactor);
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutMouseFunc(mouse);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
}