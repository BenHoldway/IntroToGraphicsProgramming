#pragma once
#include "Structures.h"

class SceneObject
{
protected:
	Mesh* mesh;

public:
	SceneObject(Mesh* _mesh);
	virtual ~SceneObject();

	virtual void Update();
	virtual void Draw();
};

