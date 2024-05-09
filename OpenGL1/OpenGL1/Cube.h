#pragma once

#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>

#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "SceneObject.h"
#include "Texture2D.h"

class Cube : public SceneObject
{
private:
	//static Vertex* indexedVertices;
	//static Colour* indexedColours;
	//static GLushort* indices;

	//static int numVertices, numColours, numIndices;
	
	Material* material;
	//Lighting* light;

	Vector3 _position;
	float rotX;
	float rotY;
	float rotZ;
	float rotationSpeed;
	float increaseAmount;

public:
	Cube(Mesh* _mesh, Texture2D* _texture, GLfloat x, GLfloat y, GLfloat z, float _rotX, float _rotY, float _rotZ, float _rotationSpeed, float _increaseAmount);
	~Cube();

	virtual void Draw();
	virtual void Update();

	void InitMat();

	//static bool Load(char* path);
	//static bool LoadObj(char* path);
};

