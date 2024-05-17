#pragma once

#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#define _USE_MATH_DEFINES
#include <math.h>

#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "SceneObject.h"
#include "Texture2D.h"

class Cube : public SceneObject
{
private:
public:
	Material* material;

	float rotX;
	float rotY;
	float rotZ;
	float rotation;
	float increaseAmount;

	float orbitRadius;
	float orbitSpeed;

	float horizontalAngle;

	bool isEmissive;

	SceneObject* parent;

	Cube(Mesh* _mesh, Texture2D* _texture, SceneObject* parentObj, GLfloat x, GLfloat y, GLfloat z, float _rotX, float _rotY, float _rotZ, float _rotationSpeed, float _increaseAmount, float _orbitRadius, float _orbitSpeed, bool _isEmissive);
	~Cube();

	virtual void Draw();
	virtual void Update();

	void InitMat();

	void Orbit();

	//static bool Load(char* path);
	//static bool LoadObj(char* path);
};

