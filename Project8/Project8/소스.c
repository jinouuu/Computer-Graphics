////////////////////////////////////////////////////////////////////
//                                                                //
// �ۼ��� : 20174054 ����ȣ                                       //
// �ۼ��� : 2020�� 5�� 17��                                       //
// ���α׷��� : Robot Arm										  //
//                                                                //
////////////////////////////////////////////////////////////////////

#include<gl/glut.h>		// �׷��� �Լ��� ���� �������

// �� ������ ȸ�� �� �˾��޴� ����� ���� ���� �ʱ�ȭ
static int shoulder = 0, elbow = 0, hand = 0;
static int finger1 = 0, finger2 = 0, finger3 = 0;
static int state = 0, state2 = 0;
GLboolean flag = GL_FALSE;

// �ʱ�ȭ �Լ�
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);	// ��� ���� ������ �ʱ�ȭ
	glShadeModel(GL_FLAT);				// ���̵� ��� FLAT ����
}

// Ư���� �ൿ �Լ�
void action(void)
{
	// flag ���� true�̸�
	if (flag)
	{
		// �� ������ ȸ���� ���� ����ŭ ����
		// ���
		if (shoulder < 10)
			shoulder = shoulder + 1;
		else if (shoulder > 10)
			shoulder = shoulder - 1;

		// �Ȳ�ġ
		if (elbow < 90)
			elbow = elbow + 1;
		else if (elbow > 90)
			elbow = elbow - 1;

		// ��
		if (hand < 45)
			hand = hand + 1;
		else if (hand > 45)
			hand = hand - 1;

		// �հ���
		if (finger1 < 45)
			finger1 = finger1 + 1;
		else if (finger1 > 45)
			finger1 = finger1 - 1;
		if (finger2 < 45)
			finger2 = finger2 + 1;
		else if (finger2 > 45)
			finger2 = finger2 - 1;
		if (finger3 < 45)
			finger3 = finger3 + 1;
		else if (finger3 > 45)
			finger3 = finger3 - 1;

		// ���� �� ���� �����ϸ� flag�� ���� false
		if (shoulder == 10 && elbow == 90 && hand == 45&&finger1==45&&finger2==45&&finger3==45)
			flag = !flag;
	}
	glutPostRedisplay();	// ����Ʈ���� ����� ����
}

// ���÷��� �Լ�
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);	// ���� �ʱ�ȭ
	glPushMatrix();					// ���� push
	gluLookAt(1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);	// ���� �̵�
	
	// ���
	glTranslatef(-2.0, 0.0, 0.0);					// ��ǥ �̵�
	glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);	// ȸ��
	glTranslatef(1.0, 0.0, 0.0);					// ��ǥ �̵�
	glPushMatrix();									// ���� push
	glScalef(2.0, 0.6, 1.0);						// ���� ��ȯ
	glutWireCube(1.0);								// wirecube
	glPopMatrix();									// ���� pop

	// �Ȳ�ġ
	glTranslatef(1.0, 0.0, 0.0);					// ��ǥ �̵�
	glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);		// ȸ��
	glTranslatef(1.0, 0.0, 0.0);					// ��ǥ �̵�
	glPushMatrix();									// ���� push
	glScalef(2.0, 0.5, 1.0);						// ���� ��ȯ
	glutWireCube(1.0);								// wirecube
	glPopMatrix();									// ���� pop

	// ��
	glTranslatef(1.0, 0.0, 0.0);					// ��ǥ �̵�
	glRotatef((GLfloat)hand, 0.0, 0.0, 1.0);		// ȸ��
	glTranslatef(0.25, 0.0, 0.0);					// ��ǥ �̵�
	glPushMatrix();									// ���� push
	glScalef(0.5, 0.5, 1.0);						// ���� ��ȯ
	glutWireCube(1.0);								// wirecube
	glPopMatrix();									// ���� pop

	// �հ���
	glTranslatef(0.25, 0.0, 0.4);					// ��ǥ �̵�
	glRotatef((GLfloat)finger1, 0.0, 0.0, 1.0);		// ȸ��
	glTranslatef(0.5, 0.0, 0.0);					// ��ǥ �̵�
	glPushMatrix();									// ���� push
	glScalef(1.0, 0.1, 0.1);						// ���� ��ȯ
	glutWireCube(1.0);								// wirecube
	glPopMatrix();									// ���� pop

	// �հ���2
	glTranslatef(-0.5, 0.0, -0.4);					// ��ǥ �̵�
	glRotatef(-(GLfloat)finger1, 0.0, 0.0, 1.0);	// ȸ���� �ʱ�ȭ
	glRotatef((GLfloat)finger2, 0.0, 0.0, 1.0);		// ȸ��
	glTranslatef(0.5, 0.0, 0.0);					// ��ǥ �̵�
	glPushMatrix();									// ���� push
	glScalef(1.0, 0.1, 0.1);						// ���� ��ȯ
	glutWireCube(1.0);								// wirecube
	glPopMatrix();									// ���� pop

	// �հ���3
	glTranslatef(-0.5, 0.0, -0.4);					// ��ǥ �̵�
	glRotatef(-(GLfloat)finger2, 0.0, 0.0, 1.0);	// ȸ���� �ʱ�ȭ
	glRotatef((GLfloat)finger3, 0.0, 0.0, 1.0);		// ȸ��
	glTranslatef(0.5, 0.0, 0.0);					// ��ǥ �̵�
	glPushMatrix();									// ���� push
	glScalef(1.0, 0.1, 0.1);						// ���� ��ȯ
	glutWireCube(1.0);								// wirecube
	glPopMatrix();									// ���� pop

	glPopMatrix();									// ���� pop
	glutSwapBuffers();								// ���� ����
}

// reshpae �Լ�
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);	// ����Ʈ ����
	glMatrixMode(GL_PROJECTION);				// ��Ʈ���� ��� �ʱ�ȭ
	glLoadIdentity();							// ��ǥ�� �ʱ�ȭ
	gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0); // ���� ���
	glMatrixMode(GL_MODELVIEW);					// ��Ʈ���� �𵨺� �ʱ�ȭ
	glLoadIdentity();							// ��ǥ�� �ʱ�ȭ
	glTranslatef(0.0, 0.0, -6.0);				// ��ǥ �̵�
}

// Ű���� �ݹ� �Լ�
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	// ȸ�� �� ����
	case'u':
		// �˾� �޴����� shoulder
		if (state == 1)
		{
			if (shoulder < 90)
				shoulder = shoulder + 1;
		}
		// �˾� �޴����� elbow
		else if (state == 2)
		{
			if (elbow < 160)
				elbow = elbow + 1;
		}
		// �˾� �޴����� hand
		else if (state == 3)
		{
			if (hand < 45)
				hand = hand + 1;
		}
		// �˾� �޴����� finger1
		else if (state == 4)
		{
			if (finger1 < 90)
				finger1 = finger1 + 1;
		}
		// �˾� �޴����� finger2
		else if (state == 5)
		{
			if (finger2 < 90)
				finger2 = finger2 + 1;
		}
		// �˾� �޴����� finger3
		else if (state == 6)
		{
			if (finger3 < 90)
				finger3 = finger3 + 1;
		}
		glutPostRedisplay();	// ���� ����
		break;

	// ȸ�� �� ����
	case'd':
		// �˾� �޴����� shoulder
		if (state == 1)
		{
			if (shoulder > -150)
				shoulder = shoulder - 1;
		}
		// �˾� �޴����� elbow
		else if (state == 2)
		{
			if (elbow > 0)
				elbow = elbow - 1;
		}
		// �˾� �޴����� hand
		else if (state == 3)
		{
			if (hand > -15)
				hand = hand - 1;
		}
		// �˾� �޴����� finger1
		else if (state == 4)
		{
			if (finger1 > 0)
				finger1 = finger1 - 1;
		}
		// �˾� �޴����� finger2
		else if (state == 5)
		{
			if (finger2 > 0)
				finger2 = finger2 - 1;
		}
		// �˾� �޴����� finger3
		else if (state == 6)
		{
			if (finger3 > 0)
				finger3 = finger3 - 1;
		}
		glutPostRedisplay();	// ���� ����
		break;

	// Ư���� �ൿ
	case's':
		flag = !flag;			// flag�� true
		glutIdleFunc(action);	// �̺�Ʈ ���� �� action �Լ� ȣ��
		break;

	// esc �Է� �� ����
	case 27:
		exit(0);
		break;
	}
}

// �˾� �޴�
void main_menu_select(int value)
{
	switch (value)
	{
	// shoulder
	case 1:
		state = 1;
		break;
	// elbow
	case 2:
		state = 2;
		break;
	// hand
	case 3:
		state = 3;
		break;
	// reset
	case 4:
		state = 0;
		shoulder = 0;
		elbow = 0;
		hand = 0;
		finger1 = 0;
		finger2 = 0;
		finger3 = 0;
		glutPostRedisplay();
		break;
	}
}

// Finger ���� �޴�
void sub_menu_select(int value)
{
	switch (value)
	{
	// finger1
	case 1:
		state = 4;
		break;
	// finger2
	case 2:
		state = 5;
		break;
	// finger3
	case 3:
		state = 6;
		break;
	}
}

// ���� �Լ�
void main(int argc, char** argv)
{
	glutInit(&argc, argv);							// GLUT ���¸� �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);	// ���÷��� ��� Double buffer & RGB Color
	glutInitWindowSize(800, 500);					// â�� ũ�� ����
	glutInitWindowPosition(100, 100);				// â�� ��ġ ����
	glutCreateWindow("Robot");						// ������ �̸� ���� �� ����
	init();

	glutDisplayFunc(display);	// display �ݹ� �Լ�
	glutReshapeFunc(reshape);	// reshape �ݹ� �Լ�
	glutKeyboardFunc(keyboard);	// keyboard �ݹ� �Լ�

	GLint SubMenu = glutCreateMenu(sub_menu_select);	// ���� �޴�
	glutAddMenuEntry("finger1",1);		// finger1
	glutAddMenuEntry("finger2", 2);		// finger2
	glutAddMenuEntry("finger3", 3);		// finger3
	glutCreateMenu(main_menu_select);	// ���� �޴�
	glutAddMenuEntry("Shoulder", 1);	// Shoulder
	glutAddMenuEntry("Elbow", 2);		// Elbow
	glutAddMenuEntry("Hand", 3);		// Hand
	glutAddSubMenu("Finger", SubMenu);	// ����޴� Finger
	glutAddMenuEntry("Reset", 4);		// Reset
	glutAttachMenu(GLUT_RIGHT_BUTTON);	// �� Ŭ�� �� �˾��޴�

	glutMainLoop();	// ���� �̺�Ʈ ó�� ����
}