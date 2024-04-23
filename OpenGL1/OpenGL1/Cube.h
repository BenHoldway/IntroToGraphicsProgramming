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

	//Mesh* mesh;

	Vector3 _position;
	float rotX;
	float rotY;
	float rotZ;
	float rotationSpeed;

public:
	Cube(GLfloat x, GLfloat y, GLfloat z, float _rotX, float _rotY, float _rotZ, float _rotationSpeed);
	~Cube();

	static bool Load(char* path);

	void Draw();

	void Update();
};

