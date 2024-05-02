#pragma once
#include "Structures.h"
#include "Texture2D.h"

class SceneObject
{
protected:
	Mesh* mesh;
	Texture2D* texture;

public:
	SceneObject(Mesh* _mesh, Texture2D* _texture);
	virtual ~SceneObject();

	virtual void Update();
	virtual void Draw();
};