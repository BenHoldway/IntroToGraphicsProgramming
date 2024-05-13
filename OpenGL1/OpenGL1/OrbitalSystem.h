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

class OrbitalSystem : public SceneObject
{
private:

	int numOfOrbiters;

	SceneObject* parent;
	SceneObject* orbiters[2];

public:
	OrbitalSystem(GLfloat x, GLfloat y, GLfloat z, int _numOfOrbiters, SceneObject* _parent, SceneObject* _orbiters[]);
	~OrbitalSystem();

	void Draw();
	void Update();
};

