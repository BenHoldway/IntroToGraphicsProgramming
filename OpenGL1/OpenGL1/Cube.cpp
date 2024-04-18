#include "Cube.h"

Vertex* Cube::indexedVertices = nullptr;
Colour* Cube::indexedColours = nullptr;
GLushort* Cube::indices = nullptr;

int Cube::numVertices = 0;
int Cube::numColours = 0;
int Cube::numIndices = 0;

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

bool Cube::Load(char* path)
{
    std::ifstream inFile;
    inFile.open(path);

    if (!inFile.good())
    {
        std::cerr << "Can't open text file " << path << std::endl;
        return false;
    }

    std::string line;
    std::getline(inFile, line);

    numVertices = std::stoi(line);
    indexedVertices = new Vertex[numVertices];

    for (int i = 0; i < numVertices; i++)
    {
        std::string line;
        std::string stringNum[3];
        int num = 0;

        std::getline(inFile, line);
        for (int x = 0; x < line.length(); x++)
        {
            stringNum[num] += line[x];
            if (line[x] == ' ')
                num++;
        }

        indexedVertices[i].x = std::stof(stringNum[0]);
        indexedVertices[i].y = std::stof(stringNum[1]);
        indexedVertices[i].z = std::stof(stringNum[2]);
    }




    std::getline(inFile, line);

    numColours = std::stoi(line);
    indexedColours = new Colour[numColours];

    for (int i = 0; i < numColours; i++)
    {
        std::string line;
        std::string stringNum[3];
        int num = 0;

        std::getline(inFile, line);
        for (int x = 0; x < line.length(); x++)
        {
            stringNum[num] += line[x];
            if (line[x] == ' ')
                num++;
        }

        indexedColours[i].r = std::stof(stringNum[0]);
        indexedColours[i].g = std::stof(stringNum[1]);
        indexedColours[i].b = std::stof(stringNum[2]);
    }

    std::getline(inFile, line);

    numColours = std::stoi(line);
    indexedColours = new Colour[numColours];

    for (int i = 0; i < numColours; i++)
    {
        std::string line;
        std::string stringNum[3];
        int num = 0;

        std::getline(inFile, line);
        for (int x = 0; x < line.length(); x++)
        {
            stringNum[num] += line[x];
            if (line[x] == ' ')
                num++;
        }

        indexedColours[i].r = std::stof(stringNum[0]);
        indexedColours[i].g = std::stof(stringNum[1]);
        indexedColours[i].b = std::stof(stringNum[2]);
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
    glRotatef(_rotation, 1.0f, 0.0f, 0.0f);
    
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, indices);
    glPopMatrix();

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void Cube::Update()
{
    _rotation += 0.3f;
    _position.z += 0.3f;

    if (_position.z > -5.0f)
    {
        _position.z = -75.0f;
    }
}
