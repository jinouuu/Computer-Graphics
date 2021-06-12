#include<GL/glut.h>
#include<GL/glu.h>
#include<stdlib.h>
#include<stdio.h>

static GLfloat spin = 0.0;
GLfloat pts[100][20];
GLint n = 0;
GLint a = 0;

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 500.0, 500.0, 0.0);
}

void spinDisplay()
{
	spin = spin + 0.1;
	if (spin > 360.0)
		spin = spin - 360.0;
	glutPostRedisplay();
}

void draw_lines()
{
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(pts[a - 1][2], pts[a - 1][12]);
	glVertex2f(pts[a][2], pts[a][12]);
	glEnd();
}

void draw_stars()
{
	int i;

	glColor3f(1.0, 0.9, 0.0);
	glBegin(GL_TRIANGLES);
	for (i = 0;i < 12;i = i + 2)
	{
		glVertex2f(pts[n][i], pts[n][i + 1]);
	}
	glEnd();
	n++;
}

void display(void)
{
	if (a > 1)
		draw_lines();

	glPushMatrix();
	draw_stars();
	glPopMatrix();

	a++;
	glutSwapBuffers();
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		pts[n][0] = x - 20;
		pts[n][1] = y - 20;
		pts[n][2] = x;
		pts[n][3] = y + 20;
		pts[n][4] = x + 20;
		pts[n][5] = y - 20;
		pts[n][6] = x - 20;
		pts[n][7] = y + 10;
		pts[n][8] = x;
		pts[n][9] = y - 30;
		pts[n][10] = x + 20;
		pts[n][11] = y + 10;
		pts[n][12] = y;
		glutPostRedisplay();
	}
	//else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("S T A R");
	init();
	glutMouseFunc(mouse);
	glutDisplayFunc(display);
	glutMainLoop();
}