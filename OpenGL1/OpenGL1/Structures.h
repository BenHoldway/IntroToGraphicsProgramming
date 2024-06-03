#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <string>

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

	int size;
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
	std::string name;
	Vector4 ambient;
	Vector4 diffuse;
	Vector4 specular;
	Vector4 emissive;

	GLfloat shininess;

	int texture;
};

struct Rotation
{
	float rotX, rotY, rotZ, rotation, increment;

	Rotation(float _x, float _y, float _z, float _rotation, float _increment)
	{
		rotX = _x;
		rotY = _y;
		rotZ = _z;
		rotation = _rotation;
		increment = _increment;
	}
};

struct Orbit
{
	GLfloat speed;
	GLfloat radius;
	GLfloat horizontalAngle;

	Orbit(GLfloat _speed, GLfloat _radius, GLfloat _angle)
	{
		speed = _speed;
		radius = _radius;
		horizontalAngle = _angle;
	}
};