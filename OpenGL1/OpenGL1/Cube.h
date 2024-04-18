#pragma once
#define NOMINMAX
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h"

class Cube
{
private:
	static Vertex* indexedVertices;
	static Colour* indexedColours;
	static GLushort* indices;

	static int numVertices, numColours, numIndices;

	GLfloat _rotation;
	Vector3 _position;

public:
	Cube(GLfloat x, GLfloat y, GLfloat z);
	~Cube();

	static bool Load(char* path);

	void Draw();
	void Update();
};

