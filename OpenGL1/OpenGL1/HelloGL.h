#pragma once

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"

#define REFRESHRATE 16

    
class HelloGL
{
public:

	float rotationSpeed1;
	float rotationSpeed2;
	float rotationSpeed3;

	bool isKeyDown;

	struct Vector3
	{
		float x;
		float y;
		float z;
	};

	struct Camera
	{
		Vector3 eye;
		Vector3 center;
		Vector3 up;
	};

	Camera* camera;

	float yAngle;
	float xAngle;

	//constructor Definition
	HelloGL(int argc, char* argv[]);

	//Destructor
	~HelloGL(void);

	void Display();
	void Update();

	float UpdateRotation(float _rotationSpeed, float increaseAmount);

	void DrawPolygon();
	void DrawTriangle(float vertex1x, float vertex1y, float vertex2x, float vertex2y, float vertex3x, float vertex3y, float rotX, float rotY, float rotZ, float rotSpeed);

	void KeyboardDown(unsigned char key, int x, int y);
	void KeyboardUp(unsigned char key, int x, int y);
	void MouseMove(int _x, int _y);

	//void DrawScalene();
	//void DrawIsosceles();
	//void DrawEquilateral();
	//void DrawAcute();
	//void DrawRightAngle();
	//void DrawObtuse();
};

