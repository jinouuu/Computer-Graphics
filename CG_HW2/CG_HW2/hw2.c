////////////////////////////////////////////////////////////////////
//                                                                //
// 작성자 : 20174054 김진호                                       //
// 작성일 : 2020년 4월 8일                                        //
// 프로그램명 : 별 그리기										  //
//                                                                //
////////////////////////////////////////////////////////////////////

#include<stdlib.h>		// 기본적인 함수 사용을 위한 헤더파일
#include<math.h>		// rand() 사용을 위한 헤더파일
#include<GL/glut.h>		// 그래픽 함수를 위한 헤더파일

#define WEIGHT 500				// 윈도우 가로 크기
#define HEIGHT 500				// 윈도우 세로 크기
#define NUMBER_OF_STARS 100		// 별의 최대 개수

static GLfloat spin = 0.0;	// 별의 회전을 위한 변수
static GLfloat ox;			// openGL 좌표 변수
static GLfloat oy;			// openGL 좌표 변수

// 처음 그려지는 별의 중점 좌표
float x = 0.0;
float y = 0.0;

GLfloat PTS[NUMBER_OF_STARS][2];	// 클릭한 좌표를 저장하기 위한 변수
GLfloat RGB[3] = { 1.0,0.9,0.0 };	// 별의 색을 지정 하기위한 배열
GLint count = 0;					// 별의 개수를 세기위한 변수
GLboolean flag = GL_FALSE;			// 회전 방향 전환을 위한 변수 선언

// 초기화 함수
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);	// 배경 색상 검은색 초기화
	glShadeModel(GL_FLAT);				// 쉐이딩 방식 FLAT 설정
}

// Reshape 콜백 함수
void reshape(int new_w, int new_h)
{
	glViewport(0, 0, new_w, new_h);				// 뷰포트 설정
	float WidthFactor = (float)new_w / 500.0;
	float HeightFactor = (float)new_h / 500.0;
	glMatrixMode(GL_PROJECTION);				// 매트릭스 모드 초기화
	glLoadIdentity();							// 좌표계 초기화

	gluOrtho2D(-1.0 * WidthFactor, 1.0 * WidthFactor, -1.0 * HeightFactor, 1.0 * HeightFactor);	// 2차원 좌표계 설정

	glMatrixMode(GL_MODELVIEW);	// 매트릭스 모델뷰 초기화
	glLoadIdentity();			// 좌표계 초기화
}

// 좌표계 변환 함수
void convertXY(int x, int y, float* ox, float* oy)
{
	int w = WEIGHT;	// 윈도우 창의 가로크기
	int h = HEIGHT;	// 윈도우 창의 세로크기

	// 윈도우 좌표계의 값을 매개변수로 받아 openGL 좌표계의 값으로 변환
	*ox = (float)(x - (float)w / 2.0) * (float)(1.0 / (float)(w / 2.0));
	*oy = -(float)(y - (float)h / 2.0) * (float)(1.0 / (float)(h / 2.0));
}

// 선 그리기 함수
void draw_lines()
{
	int i;
	glColor3f(1.0, 0.0, 0.0);	// 선의 색을 빨간색으로 초기화
	glBegin(GL_LINE_STRIP);
	glVertex2f(x, y);			// 처음 그려지는 별의 중점
	// 이후로 그려지는 별들의 중점을 선으로 이어줌
	for (i = 0;i < count;i++)
		glVertex2f(PTS[i][0], PTS[i][1]);
	glEnd();
}

// 별 그리기 함수
void draw_stars()
{
	int i;
	glColor3f(RGB[0], RGB[1], RGB[2]);	// 별의 색을 노란색으로 초기화

	glPushMatrix();						// 변환 좌표 저장
	glLoadIdentity();					// 좌표계 초기화
	glRotatef(spin, 0.0, 0.0, 1.0);		// 회전
	// 처음 그려지는 별
	glBegin(GL_TRIANGLES);
	glVertex2f(x - 0.2, y - 0.1);
	glVertex2f(x, y + 0.2);
	glVertex2f(x + 0.2, y - 0.1);
	glVertex2f(x - 0.2, y + 0.1);
	glVertex2f(x, y - 0.2);
	glVertex2f(x + 0.2, y + 0.1);
	glEnd();
	glPopMatrix();						// 저장 좌표 호출

	// 마우스 좌 클릭시 그려지는 별
	for (i = 0;i < count;i++)
	{
		glPushMatrix();									// 변환 좌표 저장
		glLoadIdentity();								// 좌표계 초기화
		glTranslatef(PTS[i][0], PTS[i][1], 0);			// 클릭 좌표로 이동
		glRotatef(spin, 0.0, 0.0, 1.0);					// 회전
		glTranslatef(-PTS[i][0], -PTS[i][1], 0);		// 처음 좌표로 이동
		// 좌 클릭시 그려지는 별
		glBegin(GL_TRIANGLES);
		glVertex2f(PTS[i][0] - 0.2, PTS[i][1] - 0.1);
		glVertex2f(PTS[i][0], PTS[i][1] + 0.2);
		glVertex2f(PTS[i][0] + 0.2, PTS[i][1] - 0.1);
		glVertex2f(PTS[i][0] - 0.2, PTS[i][1] + 0.1);
		glVertex2f(PTS[i][0], PTS[i][1] - 0.2);
		glVertex2f(PTS[i][0] + 0.2, PTS[i][1] + 0.1);
		glEnd();
		glPopMatrix();									// 저장 좌표 호출
	}
}

// 별을 회전하기 위한 함수
void spinDisplay()
{
	// flag를 이용하여 회전 방향 변경
	if (flag)
		spin = spin + 0.1;
	else
		spin = spin - 0.1;
	glutPostRedisplay();	// 현재 윈도우 새로고침
}

// 디스플레이 함수
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);	// 버퍼 초기화

	draw_stars();			// 별 그리기 함수

	draw_lines();			// 선 그리기 함수

	glutSwapBuffers();		// 프론트 버퍼와 백 버퍼 스왑
}

// 마우스 콜백 함수
void mouse(int button, int state, int x, int y)
{
	// 좌 클릭
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		convertXY(x, y, &ox, &oy);	// 좌표계 변환
		PTS[count][0] = ox;			// 변환된 x좌표값
		PTS[count][1] = oy;			// 변환된 y좌표값
		count++;					// 별의 개수 1 증가
		glutPostRedisplay();		// 프론트버퍼 백버퍼 스왑
	}
	// 휠 클릭
	else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
	{
		RGB[0] = rand() / (float)RAND_MAX * 1;	// RGB배열 R의 값 랜덤 초기화
		RGB[1] = rand() / (float)RAND_MAX * 1;	// RGB배열 G의 값 랜덤 초기화
		RGB[2] = rand() / (float)RAND_MAX * 1;	// RGB배열 B의 값 랜덤 초기화
		glutPostRedisplay();				// 프론트버퍼 백버퍼 스왑
	}
	// 우 클릭
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		flag = !flag;				// 방향 전환을 위해 flag값을 계속 변환
		glutIdleFunc(spinDisplay);	// 이벤트가 없을경우 spinDisplay 호출
	}
}

// 메인함수
void main(int argc, char** argv)
{
	glutInit(&argc, argv);							// GLUT 상태를 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);	// 디스플레이모드 Double buffer & RGB Color
	glutInitWindowSize(WEIGHT, HEIGHT);				// 창의 크기 설정
	glutInitWindowPosition(100, 100);				// 창의 위치 설정
	glutCreateWindow("S T A R");					// 윈도우 이름 설정 및 생성
	init();

	glutDisplayFunc(display);	// Display 콜백함수
	glutReshapeFunc(reshape);	// Reshape 콜백함수
	glutMouseFunc(mouse);		// Mouse 콜백함수

	glutMainLoop();				// 무한이벤트 처리루프
}