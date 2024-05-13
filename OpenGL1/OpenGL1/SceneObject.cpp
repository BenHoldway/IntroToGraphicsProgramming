#include "SceneObject.h"

SceneObject::SceneObject(Mesh* _mesh, Texture2D* _texture)
{
	mesh = _mesh;
	texture = _texture;
}

SceneObject::~SceneObject()
{

}

void SceneObject::Draw(SceneObject* parent)
{

}

void SceneObject::Update()
{

}
