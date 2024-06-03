#pragma once
#include <vector>
#include <Windows.h>
#include <iostream>
#include <fstream>

#include "Structures.h"

class Object
{
private:
	class Face
	{
	public:
		int edge;
		int* vertices;
		int* texCoords;
		int* normals;
		int currentMat;

		Face(int _currentMat, int _edge, int* _vertices, int* _texCoords, int* normal = nullptr)
		{
			this->currentMat = _currentMat;
			this->edge = _edge;
			this->vertices = _vertices;
			this->texCoords = _texCoords;
			this->normals = normal;
		}
	};

	std::vector<float*> vertices;
	std::vector<float*> texCoords;
	std::vector<float*> normals;
	std::vector<Face> faces;
	std::vector<Material> materials;

	std::vector<unsigned int> lists;
	int list = 0;

	bool hasNormals;
	bool hasTexture;


	Object* parent;
	
	Rotation* rotation;

	Orbit* orbit;
	GLfloat scale;
	Vector4* emission;


public:
	Object(std::string _name, const char* _fileName, Object* _parent, Rotation* _rotation, Orbit* _orbit, GLfloat _scale, Vector4* _emission);
	~Object();
	void Load(const char* fileName);
	unsigned int LoadTexture(const char* fileName);
	void Draw();
	void Update(bool isSpedUp);
	void OrbitPosition(bool isSpedUp);
	void OrbitPath(GLint numberOfSides);
	
	std::string name;
	Vector3 position;
	const char* fileName;
};

