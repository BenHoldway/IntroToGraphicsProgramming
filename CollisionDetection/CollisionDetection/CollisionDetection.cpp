// CollisionDetection.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <Windows.h>
#include <gl/GL.h>
#include "GL/freeglut.h"
#include <math.h>
#include <iostream>

struct Vector3
{
	float x;
	float y;
	float z;
};

struct Sphere
{
	float radius;
	Vector3 position;
};


Sphere sphere1;
Sphere sphere2;

void initSpheres();
void keyboard(unsigned char key, int x, int y);
void reshape(int w, int h);
void display(void);
void drawSpheres(float distance, bool distanceSquared);
float CalculateDistanceSquared(Sphere s1, Sphere s2);

float CalculateDistanceSquared(Sphere s1, Sphere s2)
{
	float distance =  ((s1.position.x - s2.position.x) * (s1.position.x - s2.position.x)) + ((s1.position.y - s2.position.y) * (s1.position.y - s2.position.y)) + ((s1.position.z - s2.position.z) * (s1.position.z - s2.position.z));
	return distance;
}

int main(int argc, char **argv)
{
	initSpheres();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Sphere Collisions");
	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}


void initSpheres()
{
	sphere1.radius = 1.0f;
	sphere2.radius = 1.0f;

	sphere1.position.x = -1.5f;
	sphere2.position.x = 1.5f;
}

void keyboard(unsigned char key, int x, int y) {
	if (key == 'q') {
		sphere1.position.z = sphere1.position.z - 0.1f;
	}

	if (key == 'z') {
		sphere1.position.z = sphere1.position.z + 0.1f;
	}

	if (key == 'w') {
		sphere1.position.y = sphere1.position.y + 0.1f;
	}

	if (key == 's') {
		sphere1.position.y = sphere1.position.y - 0.1f;
	}

	if (key == 'a') {
		sphere1.position.x = sphere1.position.x - 0.1f;
	}

	if (key == 'd') {
		sphere1.position.x = sphere1.position.x + 0.1f;
	}
}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

void display(void) {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(0.0, 0.0, 8.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glPointSize(5);

	float distance = CalculateDistanceSquared(sphere1, sphere2);
	drawSpheres(distance, true);

	glutSwapBuffers();
}

void drawSpheres(float distance, bool distanceSquared)
{
	float radiusDistance;
	if (distanceSquared)
		radiusDistance = pow(sphere1.radius + sphere2.radius, 2);
	else
		radiusDistance = sphere1.radius + sphere2.radius;

	//Draw Sphere 1
	glPushMatrix();
	{
		if (distance <= radiusDistance)
			glColor3f(1, 0, 0);
		else
			glColor3f(0, 0, 1);

		glTranslatef(sphere1.position.x, sphere1.position.y, sphere1.position.z);
		glBegin(GL_POINTS);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glEnd();
		glutWireSphere(sphere1.radius, 20, 20);
		glPopMatrix();

		//Draw Sphere 2
		glPushMatrix();
		glColor3f(0, 1, 0);
		glTranslatef(sphere2.position.x, sphere2.position.y, sphere2.position.z);
		glBegin(GL_POINTS);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glEnd();
		glutWireSphere(sphere2.radius, 20, 20);
	}
	glPopMatrix();
}