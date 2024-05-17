#include "Cube.h"
#include <sstream>

Cube::Cube(Mesh* _mesh, Texture2D* _texture, SceneObject* parentObj, GLfloat x, GLfloat y, GLfloat z, float _rotX, float _rotY, float _rotZ, float _rotation, float _increaseAmount, float _orbitRadius, float _orbitSpeed, bool _isEmissive) : SceneObject(_mesh, _texture)
{
    parent = parentObj;
    orbitRadius = _orbitRadius;
    orbitSpeed = _orbitSpeed;

    if (parent != nullptr)
    {
        position.x = parent->position.x - orbitRadius;
        position.y = parent->position.y;
        position.z = parent->position.z;
    }
    else
    {
        position.x = x;
        position.y = y;
        position.z = z;
    }

    rotX = _rotX;
    rotY = _rotY;
    rotZ = _rotZ;
    rotation = _rotation;
    
    increaseAmount = _increaseAmount;

    isEmissive = _isEmissive;

    horizontalAngle = 0.0f;
}

Cube::~Cube()
{
}

void Cube::Draw()
{
    if (mesh->vertices == nullptr || mesh->normals == nullptr || mesh->indices == nullptr)
        return;

    InitMat();
    glMaterialfv(GL_FRONT, GL_AMBIENT, &(material->ambient.x));
    glMaterialfv(GL_FRONT, GL_DIFFUSE, &(material->diffuse.x));
    glMaterialfv(GL_FRONT, GL_SPECULAR, &(material->specular.x));
    glMaterialf(GL_FRONT, GL_SHININESS, material->shininess);

    glBindTexture(GL_TEXTURE_2D, texture->GetID());
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    glNormalPointer(GL_FLOAT, 0, mesh->normals);
    glVertexPointer(3, GL_FLOAT, 0, mesh->vertices);

    glTexCoordPointer(2, GL_FLOAT, 0, mesh->texCoords);

    
    glPushMatrix();
    {
        glTranslatef(position.x, position.y, position.z);
        glRotatef(rotation, rotX, rotY, rotZ);

        glDrawElements(GL_TRIANGLES, mesh->indexCount, GL_UNSIGNED_SHORT, mesh->indices);
    }
    glPopMatrix();

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Cube::Update()
{
    if (parent != nullptr)
        Orbit();

    rotation += increaseAmount;

    if (rotation >= 360.0f)
        rotation = 0.0f;
}

void Cube::InitMat()
{
    material = new Material();
    material->ambient.x = 0.0f; material->ambient.y = 0.0f; material->ambient.z = 0.0f; material->ambient.w = 0.0f;
    material->diffuse.x = 0.8f; material->diffuse.y = 0.8f; material->diffuse.z = 0.8f; material->diffuse.w = 1.0f;
    material->specular.x = 1.0f; material->specular.y = 1.0f; material->specular.z = 1.0f; material->specular.w = 1.0f;
    material->shininess = 100.0f;
    if (isEmissive)
    {
        material->ambient.x = 1.0f; material->ambient.y = 1.0f; material->ambient.z = 0.0f; material->ambient.w = 1.0f;
        material->emissive.x = 0.5f; material->emissive.y = 0.5f; material->emissive.z = 0.5f; material->emissive.w = 1.0f;
        glMaterialfv(GL_FRONT, GL_EMISSION, &(material->emissive.x));
    }
}

void Cube::Orbit()
{
    horizontalAngle = fmod(horizontalAngle + orbitSpeed, M_PI * 2.0f);
    
    position.x = parent->position.x + orbitRadius * cosf(horizontalAngle) * cosf(0);
    position.y = parent->position.y + orbitRadius * sinf(0);
    position.z = parent->position.z + orbitRadius * sinf(horizontalAngle) * cosf(0);
}

//Using vertices etc...
//bool Cube::Load(char* path)
//{
//    std::ifstream inFile;
//    inFile.open(path);
//
//    if (!inFile.good())
//    {
//        std::cerr << "Can't open text file " << path << std::endl;
//        return false;
//    }
//
//    inFile >> numVertices;
//    indexedVertices = new Vertex[numVertices];
//    for (int i = 0; i < numVertices; i++)
//    {
//        inFile >> indexedVertices[i].x;
//        inFile >> indexedVertices[i].y;
//        inFile >> indexedVertices[i].z;
//    }
//    
//    inFile >> numColours;
//    indexedColours = new Colour[numColours];
//    for (int i = 0; i < numColours; i++)
//    {
//        inFile >> indexedColours[i].r;
//        inFile >> indexedColours[i].g;
//        inFile >> indexedColours[i].b;
//    }
//    
//    inFile >> numIndices;
//    indices = new GLushort[numIndices];
//    for (int i = 0; i < numIndices; i++)
//    {
//        inFile >> indices[i];
//    }
//
//    inFile.close();
//    return true;
//}
//
//bool Cube::LoadObj(char* path)
//{
//    std::ifstream inFile;
//    inFile.open(path);
//
//    if (!inFile.good())
//    {
//        std::cerr << "Can't open text file " << path << std::endl;
//        return false;
//    }
//
//    std::string str;
//    int i = 0;
//
//    while (!inFile.eof())
//    {
//        inFile >> str;
//
//        if (str == "v")
//        {
//            numVertices++;
//        }
//        else if (str == "f")
//        {
//            numIndices++;
//        }
//    }
//
//    indexedVertices = new Vertex[numVertices];
//    indices = new GLushort[numIndices];
//
//    inFile.clear();
//    inFile.seekg(0, inFile.beg);
//
//    while (!inFile.eof())
//    {
//        std::getline(inFile, str);
//
//        std::istringstream stream(str);
//        std::string token;
//
//        std::string stringArr[4];
//        int strIndex = 0;
//        int verticesIndex = 0;
//        int indicesIndex = 0;
//
//        while (std::getline(stream, token, ' '))
//        {
//            stringArr[strIndex] = token;
//            strIndex++;
//
//            if (strIndex == 4)
//            {
//                if (stringArr[0] == "v")
//                {
//                    indexedVertices[verticesIndex].x = std::stof(stringArr[1]);
//                    indexedVertices[verticesIndex].y = std::stof(stringArr[2]);
//                    indexedVertices[verticesIndex].z = std::stof(stringArr[3]);
//                    std::cout << "v " << indexedVertices[verticesIndex].x << ", " << indexedVertices[verticesIndex].y << ", " << indexedVertices[verticesIndex].z << std::endl;
//
//                    verticesIndex++;
//                }
//                else if (stringArr[0] == "f")
//                {
//                    std::cout << "f ";
//                    for (int x = 0; x < 3; x++)
//                    {
//                        indices[indicesIndex] = std::stoi(stringArr[x + 1]);
//                        std::cout << indices[indicesIndex] << ", ";
//                        indicesIndex++;
//                    }
//                    std::cout << std::endl;
//                }
//            }
//        }
//    }
//
//    inFile.close();
//    return true;
//}
