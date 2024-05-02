#include "Pyramid.h"
#include <sstream>

Pyramid::Pyramid(Mesh* _mesh, GLfloat x, GLfloat y, GLfloat z, float _rotX, float _rotY, float _rotZ, float _rotationSpeed, float _increaseAmount) : SceneObject(_mesh, nullptr)
{
    _position.x = x;
    _position.y = y;
    _position.z = z;

    rotX = _rotX;
    rotY = _rotY;
    rotZ = _rotZ;
    rotationSpeed = _rotationSpeed;

    increaseAmount = _increaseAmount;

    mesh = _mesh;
}

Pyramid::~Pyramid()
{

}

void Pyramid::Draw()
{
    if (mesh->vertices == nullptr || mesh->colours == nullptr || mesh->indices == nullptr)
        return;

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, mesh->vertices);
    glColorPointer(3, GL_FLOAT, 0, mesh->colours);

    glPushMatrix();

    glTranslatef(_position.x, _position.y, _position.z);
    glRotatef(rotationSpeed, rotX, rotY, rotZ);

    glDrawElements(GL_TRIANGLES, mesh->indexCount, GL_UNSIGNED_SHORT, mesh->indices);
    glPopMatrix();

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void Pyramid::Update()
{
    _position.z += 0.2f;
    rotationSpeed += increaseAmount;

    if (rotationSpeed >= 360.0f)
        rotationSpeed = 0.0f;

    if (_position.z > -5.0f)
    {
        _position.z = -75.0f;
    }
}
