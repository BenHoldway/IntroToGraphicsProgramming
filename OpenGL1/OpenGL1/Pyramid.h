#pragma once

#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>

#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "SceneObject.h"

class Pyramid : public SceneObject
{
private:
	Material* material;

	Vector3 _position;
	float rotX;
	float rotY;
	float rotZ;
	float rotationSpeed;
	float increaseAmount;

public:
	Pyramid(Mesh* _mesh, GLfloat x, GLfloat y, GLfloat z, float _rotX, float _rotY, float _rotZ, float _rotationSpeed, float _increaseAmount);
	~Pyramid();

	void Draw();
	void Update();
	void InitMat();
};
