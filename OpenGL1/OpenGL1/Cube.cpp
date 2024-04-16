#include "Cube.h"

Vertex Cube::indexedVertices[] = { 1, 1, 1, -1, 1, 1, // v0,v1,
                                   -1,-1, 1, 1,-1, 1, // v2,v3
                                   1,-1,-1, 1, 1,-1, // v4,v5
                                   -1, 1,-1, -1,-1,-1 }; // v6,v7

Colour Cube::indexedColours[] = { 1, 1, 1, 1, 1, 0, // v0,v1,
                                  1, 0, 0, 1, 0, 1, // v2,v3
                                  0, 0, 1, 0, 1, 1, // v4,v5
                                  0, 1, 0, 0, 0, 0 }; //v6,v7

GLushort Cube::indices[] = { 0, 1, 2, 2, 3, 0, // front
                             0, 3, 4, 4, 5, 0, // right
                             0, 5, 6, 6, 1, 0, // top
                             1, 6, 7, 7, 2, 1, // left
                             7, 4, 3, 3, 2, 7, // bottom
                             4, 7, 6, 6, 5, 4 }; // back

Cube::Cube(GLfloat x, GLfloat y, GLfloat z)
{
    _position.x = x;
    _position.y = y;
    _position.z = z;

    _rotation = 0.0f;
}

Cube::~Cube()
{
}

void Cube::Draw()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, indexedVertices);
    glColorPointer(3, GL_FLOAT, 0, indexedColours);

    glPushMatrix();
    
    glTranslatef(_position.x, _position.y, _position.z);
    glRotatef(_rotation, 1.0f, 0.0f, 0.0f);
    
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, indices);
    glPopMatrix();

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void Cube::Update()
{
    _rotation += random(-5, 5) / 10.0f;
    _position.z += 0.3f;

    if (_position.z > -5.0f)
    {
        _position.z = -75.0f;
    }
}
