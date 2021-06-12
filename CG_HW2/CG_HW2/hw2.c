////////////////////////////////////////////////////////////////////
//                                                                //
// �ۼ��� : 20174054 ����ȣ                                       //
// �ۼ��� : 2020�� 4�� 8��                                        //
// ���α׷��� : �� �׸���										  //
//                                                                //
////////////////////////////////////////////////////////////////////

#include<stdlib.h>		// �⺻���� �Լ� ����� ���� �������
#include<math.h>		// rand() ����� ���� �������
#include<GL/glut.h>		// �׷��� �Լ��� ���� �������

#define WEIGHT 500				// ������ ���� ũ��
#define HEIGHT 500				// ������ ���� ũ��
#define NUMBER_OF_STARS 100		// ���� �ִ� ����

static GLfloat spin = 0.0;	// ���� ȸ���� ���� ����
static GLfloat ox;			// openGL ��ǥ ����
static GLfloat oy;			// openGL ��ǥ ����

// ó�� �׷����� ���� ���� ��ǥ
float x = 0.0;
float y = 0.0;

GLfloat PTS[NUMBER_OF_STARS][2];	// Ŭ���� ��ǥ�� �����ϱ� ���� ����
GLfloat RGB[3] = { 1.0,0.9,0.0 };	// ���� ���� ���� �ϱ����� �迭
GLint count = 0;					// ���� ������ �������� ����
GLboolean flag = GL_FALSE;			// ȸ�� ���� ��ȯ�� ���� ���� ����

// �ʱ�ȭ �Լ�
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);	// ��� ���� ������ �ʱ�ȭ
	glShadeModel(GL_FLAT);				// ���̵� ��� FLAT ����
}

// Reshape �ݹ� �Լ�
void reshape(int new_w, int new_h)
{
	glViewport(0, 0, new_w, new_h);				// ����Ʈ ����
	float WidthFactor = (float)new_w / 500.0;
	float HeightFactor = (float)new_h / 500.0;
	glMatrixMode(GL_PROJECTION);				// ��Ʈ���� ��� �ʱ�ȭ
	glLoadIdentity();							// ��ǥ�� �ʱ�ȭ

	gluOrtho2D(-1.0 * WidthFactor, 1.0 * WidthFactor, -1.0 * HeightFactor, 1.0 * HeightFactor);	// 2���� ��ǥ�� ����

	glMatrixMode(GL_MODELVIEW);	// ��Ʈ���� �𵨺� �ʱ�ȭ
	glLoadIdentity();			// ��ǥ�� �ʱ�ȭ
}

// ��ǥ�� ��ȯ �Լ�
void convertXY(int x, int y, float* ox, float* oy)
{
	int w = WEIGHT;	// ������ â�� ����ũ��
	int h = HEIGHT;	// ������ â�� ����ũ��

	// ������ ��ǥ���� ���� �Ű������� �޾� openGL ��ǥ���� ������ ��ȯ
	*ox = (float)(x - (float)w / 2.0) * (float)(1.0 / (float)(w / 2.0));
	*oy = -(float)(y - (float)h / 2.0) * (float)(1.0 / (float)(h / 2.0));
}

// �� �׸��� �Լ�
void draw_lines()
{
	int i;
	glColor3f(1.0, 0.0, 0.0);	// ���� ���� ���������� �ʱ�ȭ
	glBegin(GL_LINE_STRIP);
	glVertex2f(x, y);			// ó�� �׷����� ���� ����
	// ���ķ� �׷����� ������ ������ ������ �̾���
	for (i = 0;i < count;i++)
		glVertex2f(PTS[i][0], PTS[i][1]);
	glEnd();
}

// �� �׸��� �Լ�
void draw_stars()
{
	int i;
	glColor3f(RGB[0], RGB[1], RGB[2]);	// ���� ���� ��������� �ʱ�ȭ

	glPushMatrix();						// ��ȯ ��ǥ ����
	glLoadIdentity();					// ��ǥ�� �ʱ�ȭ
	glRotatef(spin, 0.0, 0.0, 1.0);		// ȸ��
	// ó�� �׷����� ��
	glBegin(GL_TRIANGLES);
	glVertex2f(x - 0.2, y - 0.1);
	glVertex2f(x, y + 0.2);
	glVertex2f(x + 0.2, y - 0.1);
	glVertex2f(x - 0.2, y + 0.1);
	glVertex2f(x, y - 0.2);
	glVertex2f(x + 0.2, y + 0.1);
	glEnd();
	glPopMatrix();						// ���� ��ǥ ȣ��

	// ���콺 �� Ŭ���� �׷����� ��
	for (i = 0;i < count;i++)
	{
		glPushMatrix();									// ��ȯ ��ǥ ����
		glLoadIdentity();								// ��ǥ�� �ʱ�ȭ
		glTranslatef(PTS[i][0], PTS[i][1], 0);			// Ŭ�� ��ǥ�� �̵�
		glRotatef(spin, 0.0, 0.0, 1.0);					// ȸ��
		glTranslatef(-PTS[i][0], -PTS[i][1], 0);		// ó�� ��ǥ�� �̵�
		// �� Ŭ���� �׷����� ��
		glBegin(GL_TRIANGLES);
		glVertex2f(PTS[i][0] - 0.2, PTS[i][1] - 0.1);
		glVertex2f(PTS[i][0], PTS[i][1] + 0.2);
		glVertex2f(PTS[i][0] + 0.2, PTS[i][1] - 0.1);
		glVertex2f(PTS[i][0] - 0.2, PTS[i][1] + 0.1);
		glVertex2f(PTS[i][0], PTS[i][1] - 0.2);
		glVertex2f(PTS[i][0] + 0.2, PTS[i][1] + 0.1);
		glEnd();
		glPopMatrix();									// ���� ��ǥ ȣ��
	}
}

// ���� ȸ���ϱ� ���� �Լ�
void spinDisplay()
{
	// flag�� �̿��Ͽ� ȸ�� ���� ����
	if (flag)
		spin = spin + 0.1;
	else
		spin = spin - 0.1;
	glutPostRedisplay();	// ���� ������ ���ΰ�ħ
}

// ���÷��� �Լ�
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);	// ���� �ʱ�ȭ

	draw_stars();			// �� �׸��� �Լ�

	draw_lines();			// �� �׸��� �Լ�

	glutSwapBuffers();		// ����Ʈ ���ۿ� �� ���� ����
}

// ���콺 �ݹ� �Լ�
void mouse(int button, int state, int x, int y)
{
	// �� Ŭ��
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		convertXY(x, y, &ox, &oy);	// ��ǥ�� ��ȯ
		PTS[count][0] = ox;			// ��ȯ�� x��ǥ��
		PTS[count][1] = oy;			// ��ȯ�� y��ǥ��
		count++;					// ���� ���� 1 ����
		glutPostRedisplay();		// ����Ʈ���� ����� ����
	}
	// �� Ŭ��
	else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
	{
		RGB[0] = rand() / (float)RAND_MAX * 1;	// RGB�迭 R�� �� ���� �ʱ�ȭ
		RGB[1] = rand() / (float)RAND_MAX * 1;	// RGB�迭 G�� �� ���� �ʱ�ȭ
		RGB[2] = rand() / (float)RAND_MAX * 1;	// RGB�迭 B�� �� ���� �ʱ�ȭ
		glutPostRedisplay();				// ����Ʈ���� ����� ����
	}
	// �� Ŭ��
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		flag = !flag;				// ���� ��ȯ�� ���� flag���� ��� ��ȯ
		glutIdleFunc(spinDisplay);	// �̺�Ʈ�� ������� spinDisplay ȣ��
	}
}

// �����Լ�
void main(int argc, char** argv)
{
	glutInit(&argc, argv);							// GLUT ���¸� �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);	// ���÷��̸�� Double buffer & RGB Color
	glutInitWindowSize(WEIGHT, HEIGHT);				// â�� ũ�� ����
	glutInitWindowPosition(100, 100);				// â�� ��ġ ����
	glutCreateWindow("S T A R");					// ������ �̸� ���� �� ����
	init();

	glutDisplayFunc(display);	// Display �ݹ��Լ�
	glutReshapeFunc(reshape);	// Reshape �ݹ��Լ�
	glutMouseFunc(mouse);		// Mouse �ݹ��Լ�

	glutMainLoop();				// �����̺�Ʈ ó������
}