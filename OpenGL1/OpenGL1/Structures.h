#pragma once

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

struct Mesh
{
	Vertex* vertices;
	Colour* colours;
	GLushort* indices;
	int vertexCount, colourCount, indexCount;
};
