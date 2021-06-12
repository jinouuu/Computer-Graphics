#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>

void Init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glFlush();
}

void mouseProcess(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		printf("Left mouse button is pressed..\a\n");
	}
	else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
	{
		printf("Middle mouse button is pressed..\a\n");
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		printf("Right mouse button is pressed..\a\n");
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		printf("Left mouse button is released..\a\n");
	}
	else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_UP)
	{
		printf("Middle mouse button is released..\a\n");
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		printf("Right mouse button is released..\a\n");
	}
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Mouse and Keyboard");
	Init();
	glutDisplayFunc(display);
	glutMouseFunc(mouseProcess);
	//glutPassiveMotionFunc(mousePassiveMotion);
	//glutMotionFunc(mouseActiveMotion);
	//glutEntryFunc(mouseEntry);
	glutMainLoop();
}