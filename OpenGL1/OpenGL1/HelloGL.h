#pragma once

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h"
#include "Cube.h"
#include "Pyramid.h"
#include "MeshLoader.h"

#define REFRESHRATE 16
#define NUMOBJECTS 100

    
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

	Camera* camera;

	SceneObject* objects[NUMOBJECTS];
	SceneObject* planet;
	SceneObject* orbiter;
	SceneObject* orbitalSystem;



	//constructor Definition
	HelloGL(int argc, char* argv[]);

	//Destructor
	~HelloGL(void);

	void InitGL(int argc, char* argv[]);
	void InitObjects();
	void InitLighting();

	void Display();
	void Update();


	float UpdateRotation(float _rotationSpeed, float increaseAmount);
};

