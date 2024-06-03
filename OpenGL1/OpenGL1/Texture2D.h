#pragma once
#include <Windows.h>
#include <iostream>
#include <fstream>

#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"

class Texture2D
{
private:
	GLuint ID;
	int width, height;

public: 
	Texture2D();
	~Texture2D();

	bool Load(char* path, int _width, int _height);
	bool BMPLoad(char* path);

	GLuint GetID() const { return ID; }
	int GetWidth() const { return width; }
	int GetHeight() const { return height; }
};

