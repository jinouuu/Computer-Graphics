////////////////////////////////////////////////////////////////////
//                                                                //
// �ۼ��� : 20174054 ����ȣ                                       //
// �ۼ��� : 2020�� 4�� 22��                                       //
// ���α׷��� : Interactive ������								  //
//                                                                //
////////////////////////////////////////////////////////////////////

#include<stdlib.h>				// �⺻���� �Լ� ����� ���� �������
#include<GL/glut.h>				// �׷��� �Լ��� ���� �������

#define WEIGHT 800				// ������ ���� ũ��
#define HEIGHT 800				// ������ ���� ũ��
#define NUMBER_OF_POINTS 100	// ���� �ִ� ����

char string[10] = { 48,49,50,51,52,53,54,55,56,57 };

int mouse_state = 1;			// ���콺�� ���� ǥ��
int drag_state = 0;				// �巡�� ���� ǥ��

GLfloat PTS[NUMBER_OF_POINTS][2];	// ���� ��ǥ�� �����ϱ� ���� ����
GLfloat ox, oy;						// ��ȯ�� ��ǥ �� ������ ���� ����
GLfloat drag_x, drag_y;				// �巡��â ��ǥ�� ������ ���� ����
GLfloat mouse_x, mouse_y;			// �巡��â ��ǥ�� ������ ���� ����
GLfloat spin = 0.0;					// ȸ���� ���� ����
GLint count = 0;					// ���� ������ �������� ����

// ��ǥ�� ��ȯ �Լ�
void convertXY(int x, int y, float* ox, float* oy)
{
	int w = WEIGHT;   // ������ â�� ����ũ��
	int h = HEIGHT;   // ������ â�� ����ũ��

	// ������ ��ǥ���� ���� �Ű������� �޾� openGL ��ǥ���� ������ ��ȯ
	*ox = (float)(x - (float)w / 2.0) * (float)(1.0 / (float)(w / 2.0));
	*oy = -(float)(y - (float)h / 2.0) * (float)(1.0 / (float)(h / 2.0));
}

// �ʱ�ȭ �Լ�
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);	// ��� ���� ������ �ʱ�ȭ
	glShadeModel(GL_FLAT);				// ���̵� ��� FLAT ����
}

// Reshape �ݹ� �Լ�
void reshape(int new_w, int new_h)
{
	float WidthFactor = (float)new_w / 800.0;
	float HeightFactor = (float)new_h / 800.0;

	glViewport(0, 0, new_w, new_h);		// ����Ʈ ����
	glMatrixMode(GL_PROJECTION);		// ��Ʈ���� ��� �ʱ�ȭ
	glLoadIdentity();					// ��ǥ�� �ʱ�ȭ
	gluOrtho2D(-1.0 * WidthFactor, 1.0 * WidthFactor, -1.0 * HeightFactor, 1.0 * HeightFactor);	// 2���� ��ǥ�� ����
	glMatrixMode(GL_MODELVIEW);			// ��Ʈ���� �𵨺� �ʱ�ȭ
	glLoadIdentity();					// ��ǥ�� �ʱ�ȭ
}

// �� ��� �Լ�
void draw_points(void)
{
	int i;
	glColor3f(1.0, 0.5, 1.0);	// ���� �� ��ȫ�� �ʱ�ȭ
	glPointSize(5.0);			// ���� ũ�� 5 �ʱ�ȭ

	// ���콺�� Ŭ���� ��ǥ�� ���� ����
	for (i = 0;i < count;i++)
	{
		glPushMatrix();
		glLoadIdentity();
		glBegin(GL_POINTS);
		glVertex2f(PTS[i][0], PTS[i][1]);
		glEnd();
		glPopMatrix();
	}
}

// �� �׸��� �Լ�
void draw_lines(void)
{
	int i;
	glColor3f(1.0, 1.0, 1.0);	// ���� �� ��� �ʱ�ȭ
	glLineWidth(2.0);			// ���� ũ�� 2 �ʱ�ȭ

	// ������� ���·� ���� �׸�
	glBegin(GL_LINE_STRIP);
	for (i = 0;i < count;i++)
		glVertex2f(PTS[i][0], PTS[i][1]);
	glVertex2f(ox, oy);
	glEnd();
}

// ���� ��� �Լ�
void draw_number(void)
{
	int i;
	glColor3f(1.0, 0.0, 0.0);	// ���� �� ������ �ʱ�ȭ

	// �ݺ����� ������ �� ���� ���ڸ� ����
	for (i = 0;i < count;i++)
	{
		if (i < 10)
		{
			glRasterPos2f(PTS[i][0], PTS[i][1] + 0.01);
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[i]);
		}
		else if (i >= 10&&i<20)
		{
			glRasterPos2f(PTS[i][0], PTS[i][1] + 0.01);
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[1]);
			glRasterPos2f(PTS[i][0]+0.02, PTS[i][1] + 0.01);
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[i - 10]);
		}
		else if (i >= 20 && i < 30)
		{
			glRasterPos2f(PTS[i][0], PTS[i][1] + 0.01);
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[2]);
			glRasterPos2f(PTS[i][0] + 0.02, PTS[i][1] + 0.01);
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[i - 20]);
		}
		else if (i >= 30 && i < 40)
		{
			glRasterPos2f(PTS[i][0], PTS[i][1] + 0.01);
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[3]);
			glRasterPos2f(PTS[i][0] + 0.02, PTS[i][1] + 0.01);
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[i - 30]);
		}
		else if (i >= 40 && i < 50)
		{
			glRasterPos2f(PTS[i][0], PTS[i][1] + 0.01);
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[4]);
			glRasterPos2f(PTS[i][0] + 0.02, PTS[i][1] + 0.01);
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[i - 40]);
		}
		else if (i >= 50 && i < 60)
		{
			glRasterPos2f(PTS[i][0], PTS[i][1] + 0.01);
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[5]);
			glRasterPos2f(PTS[i][0] + 0.02, PTS[i][1] + 0.01);
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[i - 50]);
		}
		else if (i >= 60 && i < 70)
		{
			glRasterPos2f(PTS[i][0], PTS[i][1] + 0.01);
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[6]);
			glRasterPos2f(PTS[i][0] + 0.02, PTS[i][1] + 0.01);
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[i - 60]);
		}
		else if (i >= 70 && i < 80)
		{
			glRasterPos2f(PTS[i][0], PTS[i][1] + 0.01);
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[7]);
			glRasterPos2f(PTS[i][0] + 0.02, PTS[i][1] + 0.01);
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[i - 70]);
		}
		else if (i >= 80 && i < 90)
		{
			glRasterPos2f(PTS[i][0], PTS[i][1] + 0.01);
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[8]);
			glRasterPos2f(PTS[i][0] + 0.02, PTS[i][1] + 0.01);
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[i - 80]);
		}
		else if (i >= 90 && i < 100)
		{
			glRasterPos2f(PTS[i][0], PTS[i][1] + 0.01);
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[9]);
			glRasterPos2f(PTS[i][0] + 0.02, PTS[i][1] + 0.01);
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[i - 90]);
		}
	}
}

// ������ �׸��� �Լ�
void draw_polygon(void)
{
	int i;

	// �巡�� ���� ���
	if (drag_state == 1)
	{
		glPushMatrix();					// ��ȯ ��ǥ ����
		glLoadIdentity();				// ��ǥ�� �ʱ�ȭ
		glColor3f(0.1, 1.0, 0.5);		// ������ �� ������ �ʱ�ȭ
		glTranslatef(ox, oy, 0.0);		// ���콺 ��ǥ �̵�
		glRotatef(spin, 0.0, 0.0, 1.0);	// ȸ��
		glTranslatef(-ox, -oy, 0.0);	// ����

		// ���콺 ��ǥ�� ���� ������ ����
		glBegin(GL_POLYGON);
		for (i = 0;i < count;i++)
			glVertex2f(PTS[i][0] + ox, PTS[i][1] + oy);
		glEnd();
		glPopMatrix();					// ���� ��ǥ ȣ��
	}

	// �ƴ� ���
	else
	{
		glColor3f(0.5, 0.5, 0.5);	// ������ ȸ�� �ʱ�ȭ

		// ������ ����
		glBegin(GL_POLYGON);
		for (i = 0;i < count;i++)
			glVertex2f(PTS[i][0], PTS[i][1]);
		glEnd();
	}
}

// �巡�� �ڽ� �׸��� �Լ�
void draw_drag(void)
{
	glColor3f(1.0, 0.0, 0.0);		// �巡�� �ڽ� ������ �ʱ�ȭ

	// �巡�� �ڽ� ����
	glBegin(GL_LINE_LOOP);
	glVertex2f(ox, oy);
	glVertex2f(ox, mouse_y);
	glVertex2f(mouse_x, mouse_y);
	glVertex2f(mouse_x, oy);
	glEnd();
}

// ȸ�� �Լ�
void spinDisplay()
{
	spin = spin + 1.0;
	if (spin > 360)
		spin = 0.0;
	glutPostRedisplay();
}

// ���÷��� �Լ�
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);	// ���� �ʱ�ȭ

	// ��Ŭ������ �� ��� ����
	if (mouse_state == 1)
	{
		draw_points();
		draw_number();
		draw_lines();
	}

	// ��Ŭ�� �� ������ �׸���
	else if (mouse_state == 2)
	{
		draw_polygon();
	}

	// �巡�� ����
	else if (mouse_state == 3)
	{
		draw_polygon();
		draw_drag();
	}

	// �巡�� ����
	else
		draw_polygon();

	glutSwapBuffers();	// ����Ʈ���� ����� ����
}

// ���콺 �ݹ� �Լ�
void mouse(int button, int state, int x, int y)
{
	int i;		// �ݺ��� ����
	float tmp;	// �ִ밪 ������ ���� ����

	convertXY(x, y, &ox, &oy);	// ��ǥ�� ��ȯ

	// �� Ŭ��
	if (button == GLUT_LEFT_BUTTON)
	{
		// �� ���
		if (mouse_state == 1 && state == GLUT_DOWN)
		{
			PTS[count][0] = ox;		// ��ȯ�� x��ǥ��
			PTS[count][1] = oy;		// ��ȯ�� y��ǥ��
			count++;				// ���� ���� 1 ����
			glutPostRedisplay();	// ����Ʈ���� ����� ����
		}

		// �巡��
		else if (state == GLUT_DOWN && mouse_state == 2)
		{
			drag_x = ox;			// ��ȯ�� x��ǥ��
			drag_y = oy;			// ��ȯ�� y��ǥ��
			mouse_state = 3;	// ���콺 �巡������ ���·� ��ȯ
		}
		else if (state == GLUT_UP && mouse_state == 3)
		{
			drag_state = 0;		// �巡�� ���� �ʱ�ȭ
			mouse_state = 2;	// ���콺 �巡�װ��� ���·� ��ȯ

			// x �ִ밪 ����
			if (drag_x > mouse_x)
			{
				tmp = drag_x;
				drag_x = mouse_x;
				mouse_x = tmp;
			}
			// y �ִ밪 ����
			if (drag_y > mouse_y)
			{
				tmp = drag_y;
				drag_y = mouse_y;
				mouse_y = tmp;
			}

			// �巡�׳��� �������� �����ϴ��� Ȯ��
			for (i = 0;i < count;i++)
			{
				// �������� ������
				if (drag_x > PTS[i][0] || drag_y > PTS[i][1] || mouse_x < PTS[i][0] || mouse_y < PTS[i][1])
				{
					// -1
					drag_state = -1;
					break;
				}
			}

			// �����ϸ�
			if (drag_state == 0)
			{
				drag_state = 1;
				mouse_state = 4;
			}
			// �ƴϸ�
			else
				// 0
				drag_state = 0;

			glutIdleFunc(spinDisplay);	// �̺�Ʈ�� ���� ��� spinDisplay ȣ��
			glutPostRedisplay();		// ����Ʈ���� ����� ����
		}
	}

	// �� Ŭ��
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		// ���� 3�� �̻� �־�� ����
		if (mouse_state == 1 && count > 2)
		{
			mouse_state = 2;		// ���콺 �巡�װ��� ���·� ��ȯ
			glutPostRedisplay();	// ����Ʈ���� ����� ����
		}
	}

	// �� Ŭ��
	else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
	{
		mouse_state = 1;		// ���콺 ���� �ʱ�ȭ
		drag_state = 0;			// �巡�� ���� �ʱ�ȭ
		count = 0;				// �� ���� �ʱ�ȭ
		spin = 0.0;				// ���� �� �ʱ�ȭ
		glutPostRedisplay();
	}
}

// ���콺 �нú� ��� �Լ�
void mouse_passive(int x, int y)
{
	convertXY(x, y, &ox, &oy);	// ��ǥ�� ��ȯ

	// ������� ����
	if (mouse_state == 1)
		glutPostRedisplay();

	// �巡������ �������� �̵�, ȸ��
	else if (drag_state == 1)
		glutPostRedisplay();
}

// ���콺 ��� �Լ�
void mouse_motion(int x, int y)
{
	// ���콺 �巡����
	if (mouse_state == 3)
	{
		convertXY(x, y, &mouse_x, &mouse_y);
		glutPostRedisplay();
	}
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);                     // GLUT ���¸� �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);   // ���÷��̸�� Double buffer & RGB Color
	glutInitWindowSize(WEIGHT, HEIGHT);            // â�� ũ�� ����
	glutInitWindowPosition(300, 150);            // â�� ��ġ ����
	glutCreateWindow("P O L Y G O N");               // ������ �̸� ���� �� ����
	init();

	glutDisplayFunc(display);   // Display �ݹ��Լ�
	glutReshapeFunc(reshape);   // Reshape �ݹ��Լ�
	glutMouseFunc(mouse);      // Mouse �ݹ��Լ�
	glutPassiveMotionFunc(mouse_passive);	// PassiveMotion �ݹ��Լ�
	glutMotionFunc(mouse_motion);			// Motion �ݹ��Լ�

	glutMainLoop();            // �����̺�Ʈ ó������
}