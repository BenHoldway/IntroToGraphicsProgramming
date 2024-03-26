#include "HelloGL.h"
#include "GLUTCallbacks.h"


HelloGL::HelloGL(int argc, char* argv[])
{
	rotationSpeed1 = 0.0f;
	rotationSpeed2 = 0.0f;
	rotationSpeed3 = 0.0f;

	isKeyDown = false;

	camera = new Camera();
	camera->eye.x = 0.0f; camera->eye.y = 0.0f; camera->eye.z = 1.0f;
	camera->center.x = 0.0f; camera->center.y = 0.0f; camera->center.z = 0.0f;
	camera->up.x = 0.0f; camera->up.y = 1.0f; camera->up.z = 0.0f;

	GLUTCallbacks::Init(this);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Simple OpenGL Program");

	glutDisplayFunc(GLUTCallbacks::Display);
	glutKeyboardFunc(GLUTCallbacks::KeyboardDown);
	glutKeyboardUpFunc(GLUTCallbacks::KeyboardUp);
	glutPassiveMotionFunc(GLUTCallbacks::MouseMove);

	glutTimerFunc(16, GLUTCallbacks::Timer, REFRESHRATE);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, 800, 800);
	gluPerspective(45, 1, 0, 1000);
	glMatrixMode(GL_MODELVIEW);

	glutMainLoop();
}


HelloGL::~HelloGL(void)
{
	delete camera;
}

void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT); //clears the scene

	#pragma region Drawing Flat Polygons
	//DrawPolygon();

	////Scalene Triangle
	//glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
	//DrawTriangle(-0.95f, -0.25f, -0.4f, 0.25f, 0.55f, -0.25f, 1.0f, 0.5f, -1.0f, rotationSpeed1);

	////Isosceles Triangle
	//glColor4f(0.0f, 1.0f, 0.0f, 0.0f);
	//DrawTriangle(0.0f, 0.2f, 0.25f, 0.9f, 0.5f, 0.2f, 1.0f, 0.4f, 0.0f, rotationSpeed2);

	////Equilateral Triangle
	//glColor4f(0.0f, 0.0f, 1.0f, 0.0f);
	//DrawTriangle(-0.5f, -0.9f, 0.0f, -0.1f, 0.5f, -0.9f, -0.4f, 0.6f, 1.7f, rotationSpeed1);

	////Acute Triangle
	//glColor4f(1.0f, 0.0f, 1.0f, 0.0f);
	//DrawTriangle(-0.9f, 0.4f, -0.65f, 0.8f, -0.1f, 0.4f, -1.0f, 0.8f, -0.8f, rotationSpeed3);

	////Right Angle Triangle
	//glColor4f(0.4f, 0.6f, 1.0f, 0.4f);
	//DrawTriangle(0.3f, 0.5f, 0.3f, 0.8f, 0.95f, 0.5f, 0.2f, 0.8f, 0.2f, rotationSpeed3);

	////Obtuse Triangle
	//glColor4f(0.8f, 0.5f, 1.0f, 0.0f);
	//DrawTriangle(0.4f, 0.2f, 0.85f, -0.1f, 0.85f, -0.85f, 0.4f, 0.4f, -1.8f, rotationSpeed2);
#pragma endregion

	glTranslatef(0.0f, 0.0f, -5.0f);
	glutWireTeapot(0.5f);

	glFlush();
	glutSwapBuffers();
}

void HelloGL::Update()
{
	glLoadIdentity();
	//gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, camera->center.x, camera->center.y, camera->center.z, camera->up.x, camera->up.y, camera->up.z);

	glRotatef(-yAngle, 0.0f, 0.1f, 0.0f);
	glRotatef(-xAngle, 0.1f, 0.0f, 0.0f);
	glTranslatef(-camera->eye.x, -camera->eye.y, -camera->eye.z);

	glutPostRedisplay();

	rotationSpeed1 = UpdateRotation(rotationSpeed1, 4.0f);
	rotationSpeed2 = UpdateRotation(rotationSpeed2, 1.5f);
	rotationSpeed3 = UpdateRotation(rotationSpeed3, 7.5f);
}

float HelloGL::UpdateRotation(float _rotationSpeed, float increaseAmount)
{
	if (isKeyDown)
		increaseAmount *= 2;

	_rotationSpeed += increaseAmount;

	if (_rotationSpeed >= 360.0f)
		_rotationSpeed = 0.0f;

	return _rotationSpeed;
}

void HelloGL::DrawPolygon()
{
	glPushMatrix();
	glRotatef(rotationSpeed2, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, -5.0f);

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

	glPopMatrix();
}

void HelloGL::DrawTriangle(float vertex1x, float vertex1y, float vertex2x, float vertex2y, float vertex3x, float vertex3y, float rotX, float rotY, float rotZ, float rotSpeed)
{
	glPushMatrix();
	glRotatef(rotSpeed, rotX, rotY, rotZ);
	glTranslatef(0.0f, 0.0f, -5.0f);

	glBegin(GL_TRIANGLES); //starts to draw a polygon
	{
		glVertex2f(vertex1x, vertex1y);
		glVertex2f(vertex2x, vertex2y);
		glVertex2f(vertex3x, vertex3y);
		glEnd();
	}

	glPopMatrix();
}

void HelloGL::KeyboardDown(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 32:
		isKeyDown = true;
		break;
	case 'd':
		camera->eye.x += 0.01f; camera->center.x += 0.01f;
		break;
	case 'a':
		camera->eye.x -= 0.01f; camera->center.x -= 0.01f;
		break;
	case 'w':
		camera->eye.y += 0.01f; camera->center.y += 0.01f;
		break;
	case 's':
		camera->eye.y -= 0.01f; camera->center.y -= 0.01f;
		break;
	}
}

void HelloGL::KeyboardUp(unsigned char key, int x, int y)
{
	isKeyDown = false;
}

void HelloGL::MouseMove(int _x, int _y)
{
	//camera->eye.x = _x / 100;
	//camera->eye.y = _y / 100; 

	if (_y > 90)
		_y = 90;
	else if (_x < -90)
		_y = -90;

	if (_x > 360)
		_x = 360;
	else if (_x < 0)
		_x + 360;

	xAngle = _x;
	yAngle = _y;
}

//void HelloGL::DrawScalene()
//{
//	glBegin(GL_TRIANGLES); //starts to draw a polygon
//	{
//		glColor4f(1.0f, 0.0f, 0.6f, 1.0f);
//		glVertex2f(-0.75f, -0.25f);
//		glVertex2f(-0.2f, 0.25f);
//		glVertex2f(0.75f, -0.25f);
//		glEnd();
//	}
//}
//
//void HelloGL::DrawIsosceles()
//{
//	glBegin(GL_TRIANGLES); //starts to draw a polygon
//	{
//		glColor4f(1.0f, 0.0f, 0.6f, 1.0f);
//		glVertex2f(-0.3f, -0.5f);
//		glVertex2f(0.0f, 0.5f);
//		glVertex2f(0.3f, -0.5f);
//		glEnd();
//	}
//}
//
//void HelloGL::DrawEquilateral()
//{
//	glBegin(GL_TRIANGLES); //starts to draw a polygon
//	{
//		glColor4f(1.0f, 0.0f, 0.6f, 1.0f);
//		glVertex2f(-0.5f, -0.5f);
//		glVertex2f(0.0f, 0.5f);
//		glVertex2f(0.5f, -0.5f);
//		glEnd();
//	}
//}
//
//void HelloGL::DrawAcute()
//{
//	glBegin(GL_TRIANGLES); //starts to draw a polygon
//	{
//		glColor4f(1.0f, 0.0f, 0.6f, 1.0f);
//		glVertex2f(-0.5f, -0.5f);
//		glVertex2f(0.0f, 0.5f);
//		glVertex2f(0.5f, -0.5f);
//		glEnd();
//	}
//}
//
//void HelloGL::DrawRightAngle()
//{
//	glBegin(GL_TRIANGLES); //starts to draw a polygon
//	{
//		glColor4f(1.0f, 0.0f, 0.6f, 1.0f);
//		glVertex2f(-0.5f, -0.5f);
//		glVertex2f(-0.5f, 0.5f);
//		glVertex2f(0.5f, -0.5f);
//		glEnd();
//	}
//}
//
//void HelloGL::DrawObtuse()
//{
//	glBegin(GL_TRIANGLES); //starts to draw a polygon
//	{
//		glColor4f(1.0f, 0.0f, 0.6f, 1.0f);
//		glVertex2f(-0.5f, -0.5f);
//		glVertex2f(-0.75f, 0.2f);
//		glVertex2f(0.75f, -0.5f);
//		glEnd();
//	}
//}
