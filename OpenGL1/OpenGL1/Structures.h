#pragma once
#include <Windows.h>
#include <gl/GL.h>

struct Vector3
{
	float x;
	float y;
	float z;
};

struct Camera
{
	Vector3 eye;
	Vector3 center;
	Vector3 up;
};

struct Colour
{
	GLfloat r, g, b;
};

struct Vertex
{
	GLfloat x, y, z;
};

struct TexCoord
{
	GLfloat u, v;
};

struct Mesh
{
	Vertex* vertices;
	Colour* colours;
	GLushort* indices;
	int vertexCount, colourCount, indexCount, texCoordsCount;

	TexCoord* texCoords;
};