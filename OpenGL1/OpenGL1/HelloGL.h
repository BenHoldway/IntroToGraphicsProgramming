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
	//Cube* teapot;



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

	void DrawString(const char* text, Vector3* _position, Colour* _colour);

	void DrawPolygon();
	void DrawTriangle(float vertex1x, float vertex1y, float vertex2x, float vertex2y, float vertex3x, float vertex3y, float rotX, float rotY, float rotZ, float rotSpeed);

	//void DrawCube();
	//void DrawCubeArray();

	void KeyboardDown(unsigned char key, int x, int y);
	void KeyboardUp(unsigned char key, int x, int y);

	//void DrawScalene();
	//void DrawIsosceles();
	//void DrawEquilateral();
	//void DrawAcute();
	//void DrawRightAngle();
	//void DrawObtuse();
};

