#include "HelloGL.h"
#include "GLUTCallbacks.h"

HelloGL::HelloGL(int argc, char* argv[])
{
	//rotationSpeed1 = 0.0f;
	//rotationSpeed2 = 0.0f;
	//rotationSpeed3 = 0.0f;

	isKeyDown = false;

	verticalAngle = 0.0f;
	horizontalAngle = 0.0f;
	radius = 40.0f;

	mouseAngle = 0.0f;

	GLUTCallbacks::Init(this);

	InitGL(argc, argv);
	InitMenu();
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
	glutPassiveMotionFunc(GLUTCallbacks::MouseMovement);

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

void HelloGL::InitMenu()
{
	glutCreateMenu(GLUTCallbacks::CreateMenu);
	glutAddMenuEntry("Star", 0);
	glutAddMenuEntry("Planet 1", 1);
	glutAddMenuEntry("Planet 2", 2);
	glutAddMenuEntry("Cancel", -1);

	glutAttachMenu(GLUT_LEFT_BUTTON);
}

void HelloGL::ObjectSelect(int val)
{
	if (val == -1)
		return;

	cameraFocus = objects[val];
}

void HelloGL::InitObjects()
{
	camera = new Camera();
	camera->eye.x = 0.0f; camera->eye.y = 0.0f; camera->eye.z = 1.0f;
	camera->center.x = 0.0f; camera->center.y = 0.0f; camera->center.z = 0.0f;
	camera->up.x = 0.0f; camera->up.y = 1.0f; camera->up.z = 0.0f;

	Mesh* cubeMesh = MeshLoader::Load((char*)"cube.txt", true);
	Mesh* pyramidMesh = MeshLoader::Load((char*)"pyramid.txt", false);

	Texture2D* texture = new Texture2D();
	texture->Load((char*)"Penguins.raw", 512, 512);

	Texture2D* textureStars = new Texture2D();
	textureStars->Load((char*)"stars.raw", 512, 512);

	/*Parent/ Star*/ objects[0] = new Cube(cubeMesh, textureStars, nullptr, 0, 0, -10.0f, 0, 5.0f, 2.5f, 5.0f, 0.5f, 0.0f, 0.0f);
	/*Orbiter/ Planet 1*/ objects[1] = new Cube(cubeMesh, texture, objects[0], 0, 0, 0, 0.0f, 0.2f, 0.0f, 0.5f, 0.25f, 20.0f, 0.02f);
	/*Orbiter/ Planet 2*/ objects[2] = new Cube(cubeMesh, texture, objects[0], 0, 0, 0, 0.0f, 0.2f, 0.2f, 0.5f, 0.25f, 50.0f, 0.007f);

	cameraFocus = objects[0];

	//for (int i = 0; i < NUMOBJECTS / 2; i++)
	//{
	//	objects[i] = new Cube(cubeMesh, texture, 
	//		((rand() % 400) / 10.0f) - 20.0f, 
	//		((rand() % 200) / 10.0f) - 10.0f, 
	//		-(rand() % 1000) / 10.0f, 
	//		((rand() % 400) / 10.0f) - 20.0f, 
	//		((rand() % 400) / 10.0f) - 20.0f, 
	//		((rand() % 400) / 10.0f) - 20.0f, 
	//		((rand() % 400) / 20.0f) - 15.0f, 
	//		((rand() % 400) / 50.0f) - 5.0f);
	//}

	//for (int i = NUMOBJECTS / 2; i < NUMOBJECTS; i++)
	//{
	//	objects[i] = new Cube(cubeMesh, textureStars,
	//		((rand() % 400) / 10.0f) - 20.0f,
	//		((rand() % 200) / 10.0f) - 10.0f,
	//		-(rand() % 1000) / 10.0f,
	//		((rand() % 400) / 10.0f) - 20.0f,
	//		((rand() % 400) / 10.0f) - 20.0f,
	//		((rand() % 400) / 10.0f) - 20.0f,
	//		((rand() % 400) / 20.0f) - 15.0f,
	//		((rand() % 400) / 50.0f) - 5.0f);
	//}

	//for (int i = NUMOBJECTS / 2 + 50; i < NUMOBJECTS; i++)
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
	lightPos->z = -5.0f;
	lightPos->w = 1.0f;


	lightData = new Lighting();
	lightData->ambient.x = 0.1f; 
	lightData->ambient.y = 0.1f; 
	lightData->ambient.z = 0.1f; 
	lightData->ambient.w = 1.0f; 

	lightData->diffuse.x = 0.8f;
	lightData->diffuse.y = 0.8f;
	lightData->diffuse.z = 0.8f;
	lightData->diffuse.w = 1.0f;

	lightData->specular.x = 0.8f;
	lightData->specular.y = 0.8f;
	lightData->specular.z = 0.8f;
	lightData->specular.w = 1.0f;
}

HelloGL::~HelloGL(void)
{
	delete camera;
}



void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clears the scene

	for(int i = 0; i < NUMOBJECTS; i++)
		objects[i]->Draw();

	glFlush();
	glutSwapBuffers();
}

void HelloGL::Update()
{
	glLoadIdentity();
	camera->center = cameraFocus->position;

	gluLookAt
	(
		camera->center.x + radius * cosf(horizontalAngle) * cosf(verticalAngle),
		camera->center.y + radius * sinf(verticalAngle),
		camera->center.z + radius * sinf(horizontalAngle) * cosf(verticalAngle),

		camera->center.x, 
		camera->center.y,
		camera->center.z, 

		camera->up.x, 
		camera->up.y, 
		camera->up.z
	);

	glLightfv(GL_LIGHT0, GL_AMBIENT, &(lightData->ambient.x));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &(lightData->diffuse.x));
	glLightfv(GL_LIGHT0, GL_SPECULAR, &(lightData->specular.x));
	glLightfv(GL_LIGHT0, GL_POSITION, &(lightPos->x));

	
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
		radius = std::max(radius -= 0.2f, 5.0f);
		break;
	case 's':
		radius = std::min(radius += 0.2f, 15.0f);
		break;
	}

	std::cout << radius << std::endl;
}

void HelloGL::KeyboardUp(unsigned char key, int x, int y)
{
	isKeyDown = false;
}

void HelloGL::MouseMovement(int x, int y)
{
	verticalAngle = (y - 800 / 2) * 0.01f;
	horizontalAngle = (x - 800 / 2) * 0.01f;

	//mouseAngle = 90 + atan2f(camera->eye.y - verticalAngle, camera->eye.x - horizontalAngle) * 180 / M_PI;

	float max_verticalAngle = 85 * M_PI / 180;

	verticalAngle = std::max(std::min(verticalAngle, max_verticalAngle), -max_verticalAngle);
	horizontalAngle = fmod(horizontalAngle, M_PI * 2.0f);
}
