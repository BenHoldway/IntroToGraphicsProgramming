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
	Vector3* normals;
	GLushort* indices;
	int vertexCount, normalCount, indexCount, texCoordsCount;

	TexCoord* texCoords;
};

struct Vector4
{
	float x, y, z, w;
};

struct Lighting
{
	Vector4 ambient;
	Vector4 diffuse;
	Vector4 specular;
};

struct Material
{
	Vector4 ambient;
	Vector4 diffuse;
	Vector4 specular;

	GLfloat shininess;
};