#include "HelloGL.h"
#include "GLUTCallbacks.h"

HelloGL::HelloGL(int argc, char* argv[])
{
	//rotationSpeed1 = 0.0f;
	//rotationSpeed2 = 0.0f;
	//rotationSpeed3 = 0.0f;

	isKeyDown = false;

	GLUTCallbacks::Init(this);

	InitGL(argc, argv);
	InitObjects();
	InitLighting();

	glutMainLoop();
}

void HelloGL::InitGL(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Simple OpenGL Program");

	glutDisplayFunc(GLUTCallbacks::Display);
	glutKeyboardFunc(GLUTCallbacks::KeyboardDown);
	glutKeyboardUpFunc(GLUTCallbacks::KeyboardUp);

	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, 800, 800);
	gluPerspective(45, 1, 1, 1000);
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glCullFace(GL_BACK);
}

void HelloGL::InitObjects()
{
	camera = new Camera();
	camera->eye.x = 0.0f; camera->eye.y = 0.0f; camera->eye.z = 1.0f;
	camera->center.x = 0.0f; camera->center.y = 0.0f; camera->center.z = 0.0f;
	camera->up.x = 0.0f; camera->up.y = 1.0f; camera->up.z = 0.0f;

	Mesh* cubeMesh = MeshLoader::Load((char*)"cube.txt");
	//Mesh* pyramidMesh = MeshLoader::Load((char*)"pyramid.txt");

	Texture2D* texture = new Texture2D();
	texture->Load((char*)"Penguins.raw", 512, 512);


	for (int i = 0; i < NUMOBJECTS; i++)
	{
		objects[i] = new Cube(cubeMesh, texture, 
			((rand() % 400) / 10.0f) - 20.0f, 
			((rand() % 200) / 10.0f) - 10.0f, 
			-(rand() % 1000) / 10.0f, 
			((rand() % 400) / 10.0f) - 20.0f, 
			((rand() % 400) / 10.0f) - 20.0f, 
			((rand() % 400) / 10.0f) - 20.0f, 
			((rand() % 400) / 20.0f) - 15.0f, 
			((rand() % 400) / 50.0f) - 5.0f);
	}

	//for (int i = NUMOBJECTS / 2; i < NUMOBJECTS; i++)
	//{
	//	objects[i] = new Pyramid(pyramidMesh, 
	//		((rand() % 400) / 10.0f) - 20.0f, 
	//		((rand() % 200) / 10.0f) - 10.0f, 
	//		-(rand() % 1000) / 10.0f, 
	//		((rand() % 400) / 10.0f) - 20.0f, 
	//		((rand() % 400) / 10.0f) - 20.0f, 
	//		((rand() % 400) / 10.0f) - 20.0f, 
	//		((rand() % 400) / 20.0f) - 15.0f, 
	//		((rand() % 400) / 50.0f) - 5.0f);
	//}


}

void HelloGL::InitLighting()
{
	lightPos = new Vector4();
	lightPos->x = 0.0f;
	lightPos->y = 0.0f;
	lightPos->z = 1.0f;
	lightPos->w = 0.0f;


	lightData = new Lighting();
	lightData->ambient.x = 0.2f; 
	lightData->ambient.y = 0.2f; 
	lightData->ambient.z = 0.2f; 
	lightData->ambient.w = 1.0f; 

	lightData->diffuse.x = 0.8f;
	lightData->diffuse.y = 0.8f;
	lightData->diffuse.z = 0.8f;
	lightData->diffuse.w = 1.0f;

	lightData->specular.x = 0.2f;
	lightData->specular.y = 0.2f;
	lightData->specular.z = 0.2f;
	lightData->specular.w = 1.0f;
}

HelloGL::~HelloGL(void)
{
	delete camera;
	//delete cube;
}



void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clears the scene

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

	//DrawCubeArray();
	
	for(int i = 0; i < NUMOBJECTS; i++)
		objects[i]->Draw();

	glFlush();
	glutSwapBuffers();
}

void HelloGL::Update()
{
	glLoadIdentity();
	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, camera->center.x, camera->center.y, camera->center.z, camera->up.x, camera->up.y, camera->up.z);

	glLightfv(GL_LIGHT0, GL_AMBIENT, &(lightData->ambient.x));
	//glLightfv(GL_LIGHT0, GL_AMBIENT, &(lightData->ambient.y));
	//glLightfv(GL_LIGHT0, GL_AMBIENT, &(lightData->ambient.z));
	//glLightfv(GL_LIGHT0, GL_AMBIENT, &(lightData->ambient.w));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &(lightData->diffuse.x));
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, &(lightData->diffuse.y));
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, &(lightData->diffuse.z));
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, &(lightData->diffuse.w));
	glLightfv(GL_LIGHT0, GL_SPECULAR, &(lightData->specular.x));
	//glLightfv(GL_LIGHT0, GL_SPECULAR, &(lightData->specular.y));
	//glLightfv(GL_LIGHT0, GL_SPECULAR, &(lightData->specular.z));
	//glLightfv(GL_LIGHT0, GL_SPECULAR, &(lightData->specular.w));
	glLightfv(GL_LIGHT0, GL_POSITION, &(lightPos->x));
	//glLightfv(GL_LIGHT0, GL_POSITION, &(lightPos->y));
	//glLightfv(GL_LIGHT0, GL_POSITION, &(lightPos->z));
	//glLightfv(GL_LIGHT0, GL_POSITION, &(lightPos->w));

	
	for (int i = 0; i < NUMOBJECTS; i++)
		objects[i]->Update();

	glutPostRedisplay();

	//rotationSpeed1 = UpdateRotation(rotationSpeed1, 4.0f);
	//rotationSpeed2 = UpdateRotation(rotationSpeed2, 1.5f);
	//rotationSpeed3 = UpdateRotation(rotationSpeed3, 7.5f);
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




void HelloGL::DrawPolygon()
{
	glPushMatrix();
	//glRotatef(rotationSpeed2, 0.0f, 1.0f, 0.0f);
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




//void HelloGL::DrawCube()
//{
//	glBegin(GL_TRIANGLES);
//	{
//		// face v0-v1-v2
//		glColor3f(1, 1, 1);
//		glVertex3f(1, 1, 1);
//		glColor3f(1, 1, 0);
//		glVertex3f(-1, 1, 1);
//		glColor3f(1, 0, 0);
//		glVertex3f(-1, -1, 1);
//
//		// face v2-v3-v0
//		glColor3f(1, 0, 0);
//		glVertex3f(-1, -1, 1);
//		glColor3f(1, 0, 1);
//		glVertex3f(1, -1, 1);
//		glColor3f(1, 1, 1);
//		glVertex3f(1, 1, 1);
//
//		// face v0-v3-v4
//		glColor3f(1, 1, 1);
//		glVertex3f(1, 1, 1);
//		glColor3f(1, 0, 1);
//		glVertex3f(1, -1, 1);
//		glColor3f(0, 0, 1);
//		glVertex3f(1, -1, -1);
//
//		// face v4-v5-v0
//		glColor3f(0, 0, 1);
//		glVertex3f(1, -1, -1);
//		glColor3f(0, 1, 1);
//		glVertex3f(1, 1, -1);
//		glColor3f(1, 1, 1);
//		glVertex3f(1, 1, 1);
//
//		// face v0-v5-v6
//		glColor3f(1, 1, 1);
//		glVertex3f(1, 1, 1);
//		glColor3f(0, 1, 1);
//		glVertex3f(1, 1, -1);
//		glColor3f(0, 1, 0);
//		glVertex3f(-1, 1, -1);
//
//		// face v6-v1-v0
//		glColor3f(0, 1, 0);
//		glVertex3f(-1, 1, -1);
//		glColor3f(1, 1, 0);
//		glVertex3f(-1, 1, 1);
//		glColor3f(1, 1, 1);
//		glVertex3f(1, 1, 1);
//
//		// face v1-v6-v7
//		glColor3f(1, 1, 0);
//		glVertex3f(-1, 1, 1);
//		glColor3f(0, 1, 0);
//		glVertex3f(-1, 1, -1);
//		glColor3f(0, 0, 0);
//		glVertex3f(-1, -1, -1);
//
//		// face v7-v2-v1
//		glColor3f(0, 0, 0);
//		glVertex3f(-1, -1, -1);
//		glColor3f(1, 0, 0);
//		glVertex3f(-1, -1, 1);
//		glColor3f(1, 1, 0);
//		glVertex3f(-1, 1, 1);
//
//		// face v7-v4-v3
//		glColor3f(0, 0, 0);
//		glVertex3f(-1, -1, -1);
//		glColor3f(0, 0, 1);
//		glVertex3f(1, -1, -1);
//		glColor3f(1, 0, 1);
//		glVertex3f(1, -1, 1);
//
//		// face v3-v2-v7
//		glColor3f(1, 0, 1);
//		glVertex3f(1, -1, 1);
//		glColor3f(1, 0, 0);
//		glVertex3f(-1, -1, 1);
//		glColor3f(0, 0, 0);
//		glVertex3f(-1, -1, -1);
//
//		// face v4-v7-v6
//		glColor3f(0, 0, 1);
//		glVertex3f(1, -1, -1);
//		glColor3f(0, 0, 0);
//		glVertex3f(-1, -1, -1);
//		glColor3f(0, 1, 0);
//		glVertex3f(-1, 1, -1);
//
//		// face v6-v5-v4
//		glColor3f(0, 1, 0);
//		glVertex3f(-1, 1, -1);
//		glColor3f(0, 1, 1);
//		glVertex3f(1, 1, -1);
//		glColor3f(0, 0, 1);
//		glVertex3f(1, -1, -1);
//	}
//	glEnd();
//}
//
//void HelloGL::DrawCubeArray()
//{
//	glPushMatrix();
//
//	glBegin(GL_TRIANGLES);
//	{
//		for (int i = 0; i < 36; i++)
//		{
//			glColor3fv(&colours[i].r);
//			glVertex3fv(&vertices[i].x);
//		}
//		glEnd();
//
//		glPopMatrix();
//	}
//}

//void HelloGL::DrawIndexedCube()
//{
//	glPushMatrix();
//	glBegin()
//	{
//
//	}
//}



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
