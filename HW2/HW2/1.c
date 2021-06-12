////////////////////////////////////////////////////////////////////
//                                                                //
// 작성자 : 20174054 김진호                                       //
// 작성일 : 2020년 4월 22일                                       //
// 프로그램명 : Interactive 폴리곤								  //
//                                                                //
////////////////////////////////////////////////////////////////////

#include<stdlib.h>				// 기본적인 함수 사용을 위한 헤더파일
#include<GL/glut.h>				// 그래픽 함수를 위한 헤더파일

#define WEIGHT 800				// 윈도우 가로 크기
#define HEIGHT 800				// 윈도우 세로 크기
#define NUMBER_OF_POINTS 100	// 점의 최대 개수

char string[10] = { 48,49,50,51,52,53,54,55,56,57 };

int mouse_state = 1;			// 마우스의 상태 표현
int drag_state = 0;				// 드래그 상태 표현

GLfloat PTS[NUMBER_OF_POINTS][2];	// 점의 좌표를 저장하기 위한 변수
GLfloat ox, oy;						// 변환된 좌표 값 저장을 위한 변수
GLfloat drag_x, drag_y;				// 드래그창 좌표값 저장을 위한 변수
GLfloat mouse_x, mouse_y;			// 드래그창 좌표값 저장을 위한 변수
GLfloat spin = 0.0;					// 회전을 위한 변수
GLint count = 0;					// 점의 개수를 세기위한 변수

// 좌표계 변환 함수
void convertXY(int x, int y, float* ox, float* oy)
{
	int w = WEIGHT;   // 윈도우 창의 가로크기
	int h = HEIGHT;   // 윈도우 창의 세로크기

	// 윈도우 좌표계의 값을 매개변수로 받아 openGL 좌표계의 값으로 변환
	*ox = (float)(x - (float)w / 2.0) * (float)(1.0 / (float)(w / 2.0));
	*oy = -(float)(y - (float)h / 2.0) * (float)(1.0 / (float)(h / 2.0));
}

// 초기화 함수
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);	// 배경 색상 검은색 초기화
	glShadeModel(GL_FLAT);				// 쉐이딩 방식 FLAT 설정
}

// Reshape 콜백 함수
void reshape(int new_w, int new_h)
{
	float WidthFactor = (float)new_w / 800.0;
	float HeightFactor = (float)new_h / 800.0;

	glViewport(0, 0, new_w, new_h);		// 뷰포트 설정
	glMatrixMode(GL_PROJECTION);		// 매트릭스 모드 초기화
	glLoadIdentity();					// 좌표계 초기화
	gluOrtho2D(-1.0 * WidthFactor, 1.0 * WidthFactor, -1.0 * HeightFactor, 1.0 * HeightFactor);	// 2차원 좌표계 설정
	glMatrixMode(GL_MODELVIEW);			// 매트릭스 모델뷰 초기화
	glLoadIdentity();					// 좌표계 초기화
}

// 점 찍기 함수
void draw_points(void)
{
	int i;
	glColor3f(1.0, 0.5, 1.0);	// 점의 색 분홍색 초기화
	glPointSize(5.0);			// 점의 크기 5 초기화

	// 마우스로 클릭한 좌표에 점을 찍음
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

// 선 그리기 함수
void draw_lines(void)
{
	int i;
	glColor3f(1.0, 1.0, 1.0);	// 선의 색 흰색 초기화
	glLineWidth(2.0);			// 선의 크기 2 초기화

	// 러버밴드 형태로 선을 그림
	glBegin(GL_LINE_STRIP);
	for (i = 0;i < count;i++)
		glVertex2f(PTS[i][0], PTS[i][1]);
	glVertex2f(ox, oy);
	glEnd();
}

// 숫자 찍기 함수
void draw_number(void)
{
	int i;
	glColor3f(1.0, 0.0, 0.0);	// 숫자 색 빨간색 초기화

	// 반복문을 돌리며 점 위에 숫자를 찍음
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

// 폴리곤 그리기 함수
void draw_polygon(void)
{
	int i;

	// 드래그 했을 경우
	if (drag_state == 1)
	{
		glPushMatrix();					// 변환 좌표 저장
		glLoadIdentity();				// 좌표계 초기화
		glColor3f(0.1, 1.0, 0.5);		// 폴리곤 색 형광색 초기화
		glTranslatef(ox, oy, 0.0);		// 마우스 좌표 이동
		glRotatef(spin, 0.0, 0.0, 1.0);	// 회전
		glTranslatef(-ox, -oy, 0.0);	// 복구

		// 마우스 좌표에 따라 폴리곤 생성
		glBegin(GL_POLYGON);
		for (i = 0;i < count;i++)
			glVertex2f(PTS[i][0] + ox, PTS[i][1] + oy);
		glEnd();
		glPopMatrix();					// 저장 좌표 호출
	}

	// 아닌 경우
	else
	{
		glColor3f(0.5, 0.5, 0.5);	// 폴리곤 회색 초기화

		// 폴리곤 생성
		glBegin(GL_POLYGON);
		for (i = 0;i < count;i++)
			glVertex2f(PTS[i][0], PTS[i][1]);
		glEnd();
	}
}

// 드래그 박스 그리기 함수
void draw_drag(void)
{
	glColor3f(1.0, 0.0, 0.0);		// 드래그 박스 빨간색 초기화

	// 드래그 박스 생성
	glBegin(GL_LINE_LOOP);
	glVertex2f(ox, oy);
	glVertex2f(ox, mouse_y);
	glVertex2f(mouse_x, mouse_y);
	glVertex2f(mouse_x, oy);
	glEnd();
}

// 회전 함수
void spinDisplay()
{
	spin = spin + 1.0;
	if (spin > 360)
		spin = 0.0;
	glutPostRedisplay();
}

// 디스플레이 함수
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);	// 버퍼 초기화

	// 좌클릭으로 점 찍는 상태
	if (mouse_state == 1)
	{
		draw_points();
		draw_number();
		draw_lines();
	}

	// 우클릭 후 폴리곤 그리기
	else if (mouse_state == 2)
	{
		draw_polygon();
	}

	// 드래그 상태
	else if (mouse_state == 3)
	{
		draw_polygon();
		draw_drag();
	}

	// 드래그 성공
	else
		draw_polygon();

	glutSwapBuffers();	// 프론트버퍼 백버퍼 스왑
}

// 마우스 콜백 함수
void mouse(int button, int state, int x, int y)
{
	int i;		// 반복문 변수
	float tmp;	// 최대값 스왑을 위한 변수

	convertXY(x, y, &ox, &oy);	// 좌표계 변환

	// 좌 클릭
	if (button == GLUT_LEFT_BUTTON)
	{
		// 점 찍기
		if (mouse_state == 1 && state == GLUT_DOWN)
		{
			PTS[count][0] = ox;		// 변환된 x좌표값
			PTS[count][1] = oy;		// 변환된 y좌표값
			count++;				// 점의 개수 1 증가
			glutPostRedisplay();	// 프론트버퍼 백버퍼 스왑
		}

		// 드래그
		else if (state == GLUT_DOWN && mouse_state == 2)
		{
			drag_x = ox;			// 변환된 x좌표값
			drag_y = oy;			// 변환된 y좌표값
			mouse_state = 3;	// 마우스 드래그중인 상태로 전환
		}
		else if (state == GLUT_UP && mouse_state == 3)
		{
			drag_state = 0;		// 드래그 상태 초기화
			mouse_state = 2;	// 마우스 드래그가능 상태로 전환

			// x 최대값 스왑
			if (drag_x > mouse_x)
			{
				tmp = drag_x;
				drag_x = mouse_x;
				mouse_x = tmp;
			}
			// y 최대값 스왑
			if (drag_y > mouse_y)
			{
				tmp = drag_y;
				drag_y = mouse_y;
				mouse_y = tmp;
			}

			// 드래그내에 폴리곤이 존재하는지 확인
			for (i = 0;i < count;i++)
			{
				// 존재하지 않으면
				if (drag_x > PTS[i][0] || drag_y > PTS[i][1] || mouse_x < PTS[i][0] || mouse_y < PTS[i][1])
				{
					// -1
					drag_state = -1;
					break;
				}
			}

			// 존재하면
			if (drag_state == 0)
			{
				drag_state = 1;
				mouse_state = 4;
			}
			// 아니면
			else
				// 0
				drag_state = 0;

			glutIdleFunc(spinDisplay);	// 이벤트가 없을 경우 spinDisplay 호출
			glutPostRedisplay();		// 프론트버퍼 백버퍼 스왑
		}
	}

	// 우 클릭
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		// 점이 3개 이상 있어야 가능
		if (mouse_state == 1 && count > 2)
		{
			mouse_state = 2;		// 마우스 드래그가능 상태로 전환
			glutPostRedisplay();	// 프론트버퍼 백버퍼 스왑
		}
	}

	// 휠 클릭
	else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
	{
		mouse_state = 1;		// 마우스 상태 초기화
		drag_state = 0;			// 드래그 상태 초기화
		count = 0;				// 점 개수 초기화
		spin = 0.0;				// 스핀 값 초기화
		glutPostRedisplay();
	}
}

// 마우스 패시브 모션 함수
void mouse_passive(int x, int y)
{
	convertXY(x, y, &ox, &oy);	// 좌표값 변환

	// 러버밴드 구현
	if (mouse_state == 1)
		glutPostRedisplay();

	// 드래그이후 폴리곤의 이동, 회전
	else if (drag_state == 1)
		glutPostRedisplay();
}

// 마우스 모션 함수
void mouse_motion(int x, int y)
{
	// 마우스 드래그중
	if (mouse_state == 3)
	{
		convertXY(x, y, &mouse_x, &mouse_y);
		glutPostRedisplay();
	}
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);                     // GLUT 상태를 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);   // 디스플레이모드 Double buffer & RGB Color
	glutInitWindowSize(WEIGHT, HEIGHT);            // 창의 크기 설정
	glutInitWindowPosition(300, 150);            // 창의 위치 설정
	glutCreateWindow("P O L Y G O N");               // 윈도우 이름 설정 및 생성
	init();

	glutDisplayFunc(display);   // Display 콜백함수
	glutReshapeFunc(reshape);   // Reshape 콜백함수
	glutMouseFunc(mouse);      // Mouse 콜백함수
	glutPassiveMotionFunc(mouse_passive);	// PassiveMotion 콜백함수
	glutMotionFunc(mouse_motion);			// Motion 콜백함수

	glutMainLoop();            // 무한이벤트 처리루프
}