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
    if (mesh->vertices == nullptr || mesh->normals == nullptr || mesh->indices == nullptr)
        return;

    glEnableClientState(GL_VERTEX_ARRAY);
    //glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, mesh->vertices);
    //glColorPointer(3, GL_FLOAT, 0, mesh->colour);
    glNormalPointer(GL_FLOAT, 0, mesh->normals);

    InitMat();
    glMaterialfv(GL_FRONT, GL_AMBIENT, &(material->ambient.x));
    glMaterialfv(GL_FRONT, GL_DIFFUSE, &(material->diffuse.x));
    glMaterialfv(GL_FRONT, GL_SPECULAR, &(material->specular.x));
    glMaterialf(GL_FRONT, GL_SHININESS, material->shininess);

    glPushMatrix();

    glTranslatef(_position.x, _position.y, _position.z);
    glRotatef(rotationSpeed, rotX, rotY, rotZ);

    glDrawElements(GL_TRIANGLES, mesh->indexCount, GL_UNSIGNED_SHORT, mesh->indices);
    glPopMatrix();

    glDisableClientState(GL_VERTEX_ARRAY);
    //glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
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

void Pyramid::InitMat()
{
    material = new Material();
    material->ambient.x = 0.2f; material->ambient.y = 0.2f; material->ambient.z = 0.2f; material->ambient.w = 1.0f;
    material->diffuse.x = 0.0f; material->diffuse.y = 0.8f; material->diffuse.z = 0.8f; material->diffuse.w = 1.0f;
    material->specular.x = 0.0f; material->specular.y = 1.0f; material->specular.z = 1.0f; material->specular.w = 1.0f;
    material->shininess = 100.0f;
}
