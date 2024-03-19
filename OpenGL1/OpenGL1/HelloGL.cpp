#include "HelloGL.h"
#include "GLUTCallbacks.h"

HelloGL::HelloGL(int argc, char* argv[])
{
	GLUTCallbacks::Init(this);

	glutInit(&argc, argv);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Simple OpenGL Program");
	glutDisplayFunc(GLUTCallbacks::Display);
	glutMainLoop();
}


HelloGL::~HelloGL(void)
{

}

void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT); //clears the scene

	DrawPolygon();

	//Scalene Triangle
	glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
	DrawTriangle(-0.95f, -0.25f, -0.4f, 0.25f, 0.55f, -0.25f);

	//Isosceles Triangle
	glColor4f(0.0f, 1.0f, 0.0f, 0.0f);
	DrawTriangle(0.0f, 0.2f, 0.25f, 0.9f, 0.5f, 0.2f);

	//Equilateral Triangle
	glColor4f(0.0f, 0.0f, 1.0f, 0.0f);
	DrawTriangle(-0.5f, -0.9f, 0.0f, -0.1f, 0.5f, -0.9f);

	//Acute Triangle
	glColor4f(1.0f, 0.0f, 1.0f, 0.0f);
	DrawTriangle(-0.9f, 0.4f, -0.65f, 0.8f, -0.1f, 0.4f);

	//Right Angle Triangle
	glColor4f(0.4f, 0.6f, 1.0f, 0.4f);
	DrawTriangle(0.3f, 0.5f, 0.3f, 0.8f, 0.95f, 0.5f);

	//Obtuse Triangle
	glColor4f(0.8f, 0.5f, 1.0f, 0.0f);
	DrawTriangle(0.4f, 0.2f, 0.85f, -0.1f, 0.85f, -0.85f);

	glFlush();

}

void HelloGL::DrawPolygon()
{
	glBegin(GL_POLYGON); //starts to draw a polygon
	{
		glColor4f(1.0f, 0.0f, 0.6f, 1.0f);
		glVertex2f(-0.75, 0.5); //defines first point at top left
		glVertex2f(0.75, 0.5); //next point, top right
		glColor4f(0.6f, 1.0f, 0.0f, 1.0f);
		glVertex2f(0.75, -0.5); //bottom right
		glVertex2f(-0.75, -0.5); //last point, bottom left
		glEnd();
	}
}

void HelloGL::DrawTriangle(float vertex1x, float vertex1y, float vertex2x, float vertex2y, float vertex3x, float vertex3y)
{
	glBegin(GL_TRIANGLES); //starts to draw a polygon
	{
		glVertex2f(vertex1x, vertex1y);
		glVertex2f(vertex2x, vertex2y);
		glVertex2f(vertex3x, vertex3y);
		glEnd();
	}
}

void HelloGL::DrawScalene()
{
	glBegin(GL_TRIANGLES); //starts to draw a polygon
	{
		glColor4f(1.0f, 0.0f, 0.6f, 1.0f);
		glVertex2f(-0.75f, -0.25f);
		glVertex2f(-0.2f, 0.25f);
		glVertex2f(0.75f, -0.25f);
		glEnd();
	}
}

void HelloGL::DrawIsosceles()
{
	glBegin(GL_TRIANGLES); //starts to draw a polygon
	{
		glColor4f(1.0f, 0.0f, 0.6f, 1.0f);
		glVertex2f(-0.3f, -0.5f);
		glVertex2f(0.0f, 0.5f);
		glVertex2f(0.3f, -0.5f);
		glEnd();
	}
}

void HelloGL::DrawEquilateral()
{
	glBegin(GL_TRIANGLES); //starts to draw a polygon
	{
		glColor4f(1.0f, 0.0f, 0.6f, 1.0f);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(0.0f, 0.5f);
		glVertex2f(0.5f, -0.5f);
		glEnd();
	}
}

void HelloGL::DrawAcute()
{
	glBegin(GL_TRIANGLES); //starts to draw a polygon
	{
		glColor4f(1.0f, 0.0f, 0.6f, 1.0f);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(0.0f, 0.5f);
		glVertex2f(0.5f, -0.5f);
		glEnd();
	}
}

void HelloGL::DrawRightAngle()
{
	glBegin(GL_TRIANGLES); //starts to draw a polygon
	{
		glColor4f(1.0f, 0.0f, 0.6f, 1.0f);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(-0.5f, 0.5f);
		glVertex2f(0.5f, -0.5f);
		glEnd();
	}
}

void HelloGL::DrawObtuse()
{
	glBegin(GL_TRIANGLES); //starts to draw a polygon
	{
		glColor4f(1.0f, 0.0f, 0.6f, 1.0f);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(-0.75f, 0.2f);
		glVertex2f(0.75f, -0.5f);
		glEnd();
	}
}
