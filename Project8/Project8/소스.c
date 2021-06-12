////////////////////////////////////////////////////////////////////
//                                                                //
// 작성자 : 20174054 김진호                                       //
// 작성일 : 2020년 5월 17일                                       //
// 프로그램명 : Robot Arm										  //
//                                                                //
////////////////////////////////////////////////////////////////////

#include<gl/glut.h>		// 그래픽 함수를 위한 헤더파일

// 각 관절의 회전 및 팝업메뉴 사용을 위한 변수 초기화
static int shoulder = 0, elbow = 0, hand = 0;
static int finger1 = 0, finger2 = 0, finger3 = 0;
static int state = 0, state2 = 0;
GLboolean flag = GL_FALSE;

// 초기화 함수
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);	// 배경 색상 검은색 초기화
	glShadeModel(GL_FLAT);				// 쉐이딩 방식 FLAT 설정
}

// 특별한 행동 함수
void action(void)
{
	// flag 값이 true이면
	if (flag)
	{
		// 각 관절의 회전을 일정 값만큼 증가
		// 어깨
		if (shoulder < 10)
			shoulder = shoulder + 1;
		else if (shoulder > 10)
			shoulder = shoulder - 1;

		// 팔꿈치
		if (elbow < 90)
			elbow = elbow + 1;
		else if (elbow > 90)
			elbow = elbow - 1;

		// 손
		if (hand < 45)
			hand = hand + 1;
		else if (hand > 45)
			hand = hand - 1;

		// 손가락
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

		// 일정 값 까지 도달하면 flag의 값을 false
		if (shoulder == 10 && elbow == 90 && hand == 45&&finger1==45&&finger2==45&&finger3==45)
			flag = !flag;
	}
	glutPostRedisplay();	// 프론트버퍼 백버퍼 스왑
}

// 디스플레이 함수
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);	// 버퍼 초기화
	glPushMatrix();					// 스택 push
	gluLookAt(1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);	// 시점 이동
	
	// 어깨
	glTranslatef(-2.0, 0.0, 0.0);					// 좌표 이동
	glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);	// 회전
	glTranslatef(1.0, 0.0, 0.0);					// 좌표 이동
	glPushMatrix();									// 스택 push
	glScalef(2.0, 0.6, 1.0);						// 비율 변환
	glutWireCube(1.0);								// wirecube
	glPopMatrix();									// 스택 pop

	// 팔꿈치
	glTranslatef(1.0, 0.0, 0.0);					// 좌표 이동
	glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);		// 회전
	glTranslatef(1.0, 0.0, 0.0);					// 좌표 이동
	glPushMatrix();									// 스택 push
	glScalef(2.0, 0.5, 1.0);						// 비율 변환
	glutWireCube(1.0);								// wirecube
	glPopMatrix();									// 스택 pop

	// 손
	glTranslatef(1.0, 0.0, 0.0);					// 좌표 이동
	glRotatef((GLfloat)hand, 0.0, 0.0, 1.0);		// 회전
	glTranslatef(0.25, 0.0, 0.0);					// 좌표 이동
	glPushMatrix();									// 스택 push
	glScalef(0.5, 0.5, 1.0);						// 비율 변환
	glutWireCube(1.0);								// wirecube
	glPopMatrix();									// 스택 pop

	// 손가락
	glTranslatef(0.25, 0.0, 0.4);					// 좌표 이동
	glRotatef((GLfloat)finger1, 0.0, 0.0, 1.0);		// 회전
	glTranslatef(0.5, 0.0, 0.0);					// 좌표 이동
	glPushMatrix();									// 스택 push
	glScalef(1.0, 0.1, 0.1);						// 비율 변환
	glutWireCube(1.0);								// wirecube
	glPopMatrix();									// 스택 pop

	// 손가락2
	glTranslatef(-0.5, 0.0, -0.4);					// 좌표 이동
	glRotatef(-(GLfloat)finger1, 0.0, 0.0, 1.0);	// 회전값 초기화
	glRotatef((GLfloat)finger2, 0.0, 0.0, 1.0);		// 회전
	glTranslatef(0.5, 0.0, 0.0);					// 좌표 이동
	glPushMatrix();									// 스택 push
	glScalef(1.0, 0.1, 0.1);						// 비율 변환
	glutWireCube(1.0);								// wirecube
	glPopMatrix();									// 스택 pop

	// 손가락3
	glTranslatef(-0.5, 0.0, -0.4);					// 좌표 이동
	glRotatef(-(GLfloat)finger2, 0.0, 0.0, 1.0);	// 회전값 초기화
	glRotatef((GLfloat)finger3, 0.0, 0.0, 1.0);		// 회전
	glTranslatef(0.5, 0.0, 0.0);					// 좌표 이동
	glPushMatrix();									// 스택 push
	glScalef(1.0, 0.1, 0.1);						// 비율 변환
	glutWireCube(1.0);								// wirecube
	glPopMatrix();									// 스택 pop

	glPopMatrix();									// 스택 pop
	glutSwapBuffers();								// 버퍼 스왑
}

// reshpae 함수
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);	// 뷰포트 설정
	glMatrixMode(GL_PROJECTION);				// 매트릭스 모드 초기화
	glLoadIdentity();							// 좌표계 초기화
	gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0); // 투영 행렬
	glMatrixMode(GL_MODELVIEW);					// 매트릭스 모델뷰 초기화
	glLoadIdentity();							// 좌표계 초기화
	glTranslatef(0.0, 0.0, -6.0);				// 좌표 이동
}

// 키보드 콜백 함수
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	// 회전 각 증가
	case'u':
		// 팝업 메뉴에서 shoulder
		if (state == 1)
		{
			if (shoulder < 90)
				shoulder = shoulder + 1;
		}
		// 팝업 메뉴에서 elbow
		else if (state == 2)
		{
			if (elbow < 160)
				elbow = elbow + 1;
		}
		// 팝업 메뉴에서 hand
		else if (state == 3)
		{
			if (hand < 45)
				hand = hand + 1;
		}
		// 팝업 메뉴에서 finger1
		else if (state == 4)
		{
			if (finger1 < 90)
				finger1 = finger1 + 1;
		}
		// 팝업 메뉴에서 finger2
		else if (state == 5)
		{
			if (finger2 < 90)
				finger2 = finger2 + 1;
		}
		// 팝업 메뉴에서 finger3
		else if (state == 6)
		{
			if (finger3 < 90)
				finger3 = finger3 + 1;
		}
		glutPostRedisplay();	// 버퍼 스왑
		break;

	// 회전 각 감소
	case'd':
		// 팝업 메뉴에서 shoulder
		if (state == 1)
		{
			if (shoulder > -150)
				shoulder = shoulder - 1;
		}
		// 팝업 메뉴에서 elbow
		else if (state == 2)
		{
			if (elbow > 0)
				elbow = elbow - 1;
		}
		// 팝업 메뉴에서 hand
		else if (state == 3)
		{
			if (hand > -15)
				hand = hand - 1;
		}
		// 팝업 메뉴에서 finger1
		else if (state == 4)
		{
			if (finger1 > 0)
				finger1 = finger1 - 1;
		}
		// 팝업 메뉴에서 finger2
		else if (state == 5)
		{
			if (finger2 > 0)
				finger2 = finger2 - 1;
		}
		// 팝업 메뉴에서 finger3
		else if (state == 6)
		{
			if (finger3 > 0)
				finger3 = finger3 - 1;
		}
		glutPostRedisplay();	// 버퍼 스왑
		break;

	// 특별한 행동
	case's':
		flag = !flag;			// flag값 true
		glutIdleFunc(action);	// 이벤트 없을 시 action 함수 호출
		break;

	// esc 입력 시 종료
	case 27:
		exit(0);
		break;
	}
}

// 팝업 메뉴
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

// Finger 서브 메뉴
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

// 메인 함수
void main(int argc, char** argv)
{
	glutInit(&argc, argv);							// GLUT 상태를 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);	// 디스플레이 모드 Double buffer & RGB Color
	glutInitWindowSize(800, 500);					// 창의 크기 설정
	glutInitWindowPosition(100, 100);				// 창의 위치 설정
	glutCreateWindow("Robot");						// 윈도우 이름 설정 및 생성
	init();

	glutDisplayFunc(display);	// display 콜백 함수
	glutReshapeFunc(reshape);	// reshape 콜백 함수
	glutKeyboardFunc(keyboard);	// keyboard 콜백 함수

	GLint SubMenu = glutCreateMenu(sub_menu_select);	// 서브 메뉴
	glutAddMenuEntry("finger1",1);		// finger1
	glutAddMenuEntry("finger2", 2);		// finger2
	glutAddMenuEntry("finger3", 3);		// finger3
	glutCreateMenu(main_menu_select);	// 메인 메뉴
	glutAddMenuEntry("Shoulder", 1);	// Shoulder
	glutAddMenuEntry("Elbow", 2);		// Elbow
	glutAddMenuEntry("Hand", 3);		// Hand
	glutAddSubMenu("Finger", SubMenu);	// 서브메뉴 Finger
	glutAddMenuEntry("Reset", 4);		// Reset
	glutAttachMenu(GLUT_RIGHT_BUTTON);	// 우 클릭 시 팝업메뉴

	glutMainLoop();	// 무한 이벤트 처리 루프
}