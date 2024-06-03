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
	InitObjects();
	InitLighting();
	
	InitMenu();

	glutMainLoop();
}

void HelloGL::InitGL(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(1920, 1080);
	glutCreateWindow("Simple OpenGL Program");

	glutDisplayFunc(GLUTCallbacks::Display);
	glutKeyboardFunc(GLUTCallbacks::KeyboardDown);
	glutKeyboardUpFunc(GLUTCallbacks::KeyboardUp);
	glutPassiveMotionFunc(GLUTCallbacks::MouseMovement);
	glutMouseWheelFunc(GLUTCallbacks::MouseWheel);

	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);

	//Allows access to modify camera's perspective and aspect ratio etc
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, 1920, 1080);
	gluPerspective(45, 1920/1080, 1, 1000);

	glutFullScreen();

	//Allows access to transform, rotate, scale etc different objects
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glCullFace(GL_BACK);

	//glutSetCursor(GLUT_CURSOR_NONE);

	//glutReshapeWindow(1920, 1080);
}

void HelloGL::InitMenu()
{
	glutCreateMenu(GLUTCallbacks::CreateMenu);
	glutAddMenuEntry(system->objects[0]->name.c_str(), 0);
	glutAddMenuEntry(system->objects[1]->name.c_str(), 1);
	glutAddMenuEntry(system->objects[2]->name.c_str(), 2);
	glutAddMenuEntry(system->objects[3]->name.c_str(), 3);
	//glutAddMenuEntry(system->objects[4]->name.c_str(), 4);
	//glutAddMenuEntry(system->objects[5]->name.c_str(), 5);
	//glutAddMenuEntry(system->objects[6]->name.c_str(), 6);
	glutAddMenuEntry("Cancel", -1);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void HelloGL::InitObjects()
{
	camera = new Camera();
	camera->eye.x = 0.0f; camera->eye.y = 0.0f; camera->eye.z = 1.0f;
	camera->center.x = 0.0f; camera->center.y = 0.0f; camera->center.z = 0.0f;
	camera->up.x = 0.0f; camera->up.y = 1.0f; camera->up.z = 0.0f;

	system = new OrbitSystem();

	cameraFocus = system->objects[0];
}

void HelloGL::InitLighting()
{
	lightPos = new Vector4();
	lightPos->x = system->objects[0]->position.x;
	lightPos->y = system->objects[0]->position.y;
	lightPos->z = system->objects[0]->position.z;
	lightPos->w = 1.0f;


	lightData = new Lighting();
	lightData->ambient.x = 0.0f; 
	lightData->ambient.y = 0.0f; 
	lightData->ambient.z = 0.0f; 
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

void HelloGL::ObjectSelect(int val)
{
	if (val == -1)
		return;

	cameraFocus = system->objects[val];
}


void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clears the scene

	system->Draw();

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

	
	system->Update();

	glutPostRedisplay();
}

void HelloGL::KeyboardDown(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 32:
			isKeyDown = true;
			break;
		case 'w':
			radius = std::max(radius -= 0.2f, 10.0f);
			break;
		case 's':
			radius = std::min(radius += 0.2f, 30.0f);
			break;
		case 27:
			glutDestroyWindow(glutGetWindow());
			break;
	}
}

void HelloGL::KeyboardUp(unsigned char key, int x, int y)
{
	isKeyDown = false;
}

void HelloGL::MouseMovement(int x, int y)
{
	verticalAngle = (y - 800 / 2) * 0.01f;
	horizontalAngle = (x - 800 / 2) * 0.01f;

	float max_verticalAngle = 85 * M_PI / 180;

	verticalAngle = std::max(std::min(verticalAngle, max_verticalAngle), -max_verticalAngle);
	horizontalAngle = fmod(horizontalAngle, M_PI * 2.0f);
}

void HelloGL::MouseWheel(int wheel, int direction, int x, int y)
{
	if(direction > 0)
		radius = std::max(radius -= 0.75f, 10.0f);
	else
		radius = std::min(radius += 0.75f, 30.0f);
}
