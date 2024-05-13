#pragma once
#include "Structures.h"
#include "Texture2D.h"

class SceneObject
{
protected:
	Mesh* mesh;
	Texture2D* texture;
	Material* material;
public:
	Vector3 position;

	SceneObject(Mesh* _mesh, Texture2D* _texture);
	virtual ~SceneObject();

	virtual void Draw();
	virtual void Update();
};