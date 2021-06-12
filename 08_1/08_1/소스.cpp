#include<iostream>
#include<GL/glut.h>
#include<vector>
#include"lodepng.h"

float rotation = 0.0f;
float angularVelocity = 1.5f;
GLuint textureID[2];
std::vector<unsigned char> image2;
void loadTexture(GLuint* texture, char* path);

void render()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glOrtho(-100.0f, 100.0f, -100.0f, 100.0f, -100.0f, 100.0f);
	giViewport(0, 0, 500, 500);

	glPushMatrix();
	glRotatef(rotation, 0.0f, 1.0f, 0.0f);

	glBindTexture(GL_TEXTURE_2D, textureID[0]);
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-50.0f, -50.0f, 0.0f);
	glTexCoord2f(0.5f, 0.0f); glVertex3f(0.0f, 50.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(50.0f, -50.0f, 0.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textureID[1]);
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.5f, 0.0f); glVertex3f(0.0f, 50.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
}
