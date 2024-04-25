#include "Cube.h"
#include <sstream>

Vertex* Cube::indexedVertices = nullptr;
Colour* Cube::indexedColours = nullptr;
GLushort* Cube::indices = nullptr;

int Cube::numVertices = 0;
int Cube::numColours = 0;
int Cube::numIndices = 0;

Cube::Cube(GLfloat x, GLfloat y, GLfloat z, float _rotX, float _rotY, float _rotZ, float _rotationSpeed)
{
    _position.x = x;
    _position.y = y;
    _position.z = z;

    rotX = _rotX;
    rotY = _rotY;
    rotZ = _rotZ;
    rotationSpeed = _rotationSpeed;
}

Cube::~Cube()
{
}

bool Cube::Load(char* path)
{
    std::ifstream inFile;
    inFile.open(path);

    if (!inFile.good())
    {
        std::cerr << "Can't open text file " << path << std::endl;
        return false;
    }

    inFile >> numVertices;
    indexedVertices = new Vertex[numVertices];
    for (int i = 0; i < numVertices; i++)
    {
        inFile >> indexedVertices[i].x;
        inFile >> indexedVertices[i].y;
        inFile >> indexedVertices[i].z;
    }
    
    inFile >> numColours;
    indexedColours = new Colour[numColours];
    for (int i = 0; i < numColours; i++)
    {
        inFile >> indexedColours[i].r;
        inFile >> indexedColours[i].g;
        inFile >> indexedColours[i].b;
    }
    
    inFile >> numIndices;
    indices = new GLushort[numIndices];
    for (int i = 0; i < numIndices; i++)
    {
        inFile >> indices[i];
    }

    inFile.close();
    return true;
}

bool Cube::LoadObj(char* path)
{
    std::ifstream inFile;
    inFile.open(path);

    if (!inFile.good())
    {
        std::cerr << "Can't open text file " << path << std::endl;
        return false;
    }

    std::string str;
    int i = 0;

    while (!inFile.eof())
    {
        inFile >> str;

        if (str == "v")
        {
            numVertices++;
        }
        else if (str == "f")
        {
            numIndices++;
        }
    }

    indexedVertices = new Vertex[numVertices];
    indices = new GLushort[numIndices];

    inFile.clear();
    inFile.seekg(0, inFile.beg);

    while (!inFile.eof())
    {
        std::getline(inFile, str);

        std::istringstream stream(str);
        std::string token;

        std::string stringArr[4];
        int strIndex = 0;
        int verticesIndex = 0;
        int indicesIndex = 0;

        while (std::getline(stream, token, ' '))
        {
            stringArr[strIndex] = token;
            strIndex++;

            if (strIndex == 4)
            {
                if (stringArr[0] == "v")
                {
                    indexedVertices[verticesIndex].x = std::stoul(stringArr[1]);
                    indexedVertices[verticesIndex].y = std::stoul(stringArr[2]);
                    indexedVertices[verticesIndex].z = std::stoul(stringArr[3]);
                    verticesIndex++;
                }
                else if (stringArr[0] == "f")
                {
                    for (int x = 0; x < 3; x++)
                    {
                        indices[indicesIndex] = std::stoi(stringArr[x + 1]);
                        indicesIndex++;
                    }
                }
            }
        }
    }

    inFile.close();
    return true;
}

void Cube::Draw()
{
    if (indexedVertices == nullptr || indexedColours == nullptr || indices == nullptr)
        return;

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, indexedVertices);
    glColorPointer(3, GL_FLOAT, 0, indexedColours);

    glPushMatrix();
    
    glTranslatef(_position.x, _position.y, _position.z);
    glRotatef(rotationSpeed, rotX, rotY, rotZ);
    
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, indices);
    glPopMatrix();

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void Cube::Update()
{
    _position.z += 0.3f;
    rotX += rotationSpeed;
    rotY += rotationSpeed;
    rotZ += rotationSpeed;

    if (_position.z > -5.0f)
    {
        _position.z = -75.0f;
    }
}
