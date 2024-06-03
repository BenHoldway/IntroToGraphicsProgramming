#pragma once

#define NOMINMAX
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "GL\freeglut.h"
#include "Structures.h"
#include "Cube.h"
#include "Pyramid.h"
#include "MeshLoader.h"
#include "OrbitSystem.h"
#include "Object.h"

#define REFRESHRATE 16
#define NUMOBJECTS 3

    
class HelloGL
{
private:
	Vector4* lightPos;
	Lighting* lightData;
public:

	//float rotationSpeed1;
	//float rotationSpeed2;
	//float rotationSpeed3;

	bool isKeyDown;

	float verticalAngle;
	float horizontalAngle;
	float radius;

	float mouseAngle;

	Camera* camera;

	OrbitSystem* system;
	Object* cameraFocus;

	//constructor Definition
	HelloGL(int argc, char* argv[]);

	//Destructor
	~HelloGL(void);

	void InitGL(int argc, char* argv[]);
	void InitMenu();
	void InitObjects();
	void InitLighting();

	void ObjectSelect(int val);

	void Display();
	void Update();

	void KeyboardDown(unsigned char key, int x, int y);
	void KeyboardUp(unsigned char key, int x, int y);
	void MouseMovement(int x, int y);
	void MouseWheel(int wheel, int direction, int x, int y);
};

