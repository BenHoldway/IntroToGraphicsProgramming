#pragma once

#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>

#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "SceneObject.h"

class Cube : public SceneObject
{
private:
	//static Vertex* indexedVertices;
	//static Colour* indexedColours;
	//static GLushort* indices;

	//static int numVertices, numColours, numIndices;

	Vector3 _position;
	float rotX;
	float rotY;
	float rotZ;
	float rotationSpeed;
	float increaseAmount;

public:
	Cube(Mesh* _mesh, GLfloat x, GLfloat y, GLfloat z, float _rotX, float _rotY, float _rotZ, float _rotationSpeed, float _increaseAmount);
	~Cube();

	//static bool Load(char* path);
	//static bool LoadObj(char* path);
};

