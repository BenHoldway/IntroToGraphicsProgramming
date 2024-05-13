#include "OrbitalSystem.h"
OrbitalSystem::OrbitalSystem(GLfloat x, GLfloat y, GLfloat z, int _numOfOrbiters, SceneObject* _parent, SceneObject* _orbiters[]) : SceneObject(nullptr, nullptr)
{
    position.x = x;
    position.y = y;
    position.z = z;

    numOfOrbiters = _numOfOrbiters;
    parent = _parent;

    for (int i = 0; i < 2; i++)
        orbiters[i] = _orbiters[i];
}

OrbitalSystem::~OrbitalSystem()
{
}

void OrbitalSystem::Draw()
{
    glPushMatrix();
    {
        glTranslatef(position.x, position.y, position.z);

        for (int i = 0; i < 2; i++)
            orbiters[i]->Draw(parent);
    }
    glPopMatrix();
}