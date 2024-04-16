#pragma once
#define NOMINMAX
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h"
#include "Random.h"

class Cube
{
private:
	static Vertex indexedVertices[];
	static Colour indexedColours[];
	static GLushort indices[];

	GLfloat _rotation;
	Vector3 _position;

public:
	Cube(GLfloat x, GLfloat y, GLfloat z);
	~Cube();

	void Draw();
	void Update();
};

