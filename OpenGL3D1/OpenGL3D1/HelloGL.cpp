#include "HelloGL.h"
#include "GLUTCallbacks.h"
#include <iostream>

HelloGL::HelloGL(int argc, char* argv[])
{
	vertices = new point3D();
	colours = new colour();
	indices = new polygon();

	GLUTCallbacks::Init(this);

	glutInit(&argc, argv);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Simple OpenGL Program");
	glutDisplayFunc(GLUTCallbacks::Display);

	glutTimerFunc(16, GLUTCallbacks::Timer, REFRESHRATE);

	glutMainLoop();
}


HelloGL::~HelloGL(void)
{

}

void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT); //clears the scene

	DrawCube();

	glFlush();
}

void HelloGL::Update()
{

}

void HelloGL::DrawPolygon(int a, int b, int c, int d)
{
	glBegin(GL_QUADS);
	{
		glVertex3fv(&vertices[a].x);
		glVertex3fv(&vertices[b].x);
		glVertex3fv(&vertices[c].x);
		glVertex3fv(&vertices[d].x);
	}
	glEnd();
}

void HelloGL::DrawCube()
{
	for (int i = 0; i < 6; i++)
	{
		glColor3f(colours[i].r, colours[i].g, colours[i].b);
		DrawPolygon(indices[i].a, indices[i].b, indices[i].c, indices[i].d);
	}
}
