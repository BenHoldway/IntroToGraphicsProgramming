#pragma once

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"


class HelloGL
{
public:
	//constructor Definition
	HelloGL(int argc, char* argv[]);

	//Destructor
	~HelloGL(void);

	void Display();

	void DrawPolygon();
	void DrawTriangle(float vertex1x, float vertex1y, float vertex2x, float vertex2y, float vertex3x, float vertex3y);

	void DrawScalene();
	void DrawIsosceles();
	void DrawEquilateral();
	void DrawAcute();
	void DrawRightAngle();
	void DrawObtuse();
};

