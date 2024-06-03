#include "MeshLoader.h"

#include <iostream>
#include <fstream>

using namespace std;

namespace MeshLoader
{
	void LoadVertices(ifstream& inFile, Mesh& mesh);
	void LoadTexCoords(ifstream& inFile, Mesh& mesh);
	void LoadNormals(ifstream& inFile, Mesh& mesh);
	void LoadIndices(ifstream& inFile, Mesh& mesh);

	void LoadVertices(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.vertexCount;

		if (mesh.vertexCount > 0)
		{
			mesh.vertices = new Vertex[mesh.vertexCount];

			for (int i = 0; i < mesh.vertexCount; i++)
			{
				inFile >> mesh.vertices[i].x;
				inFile >> mesh.vertices[i].y;
				inFile >> mesh.vertices[i].z;

				mesh.vertices[i].x *= mesh.size;
				mesh.vertices[i].y *= mesh.size;
				mesh.vertices[i].z *= mesh.size;
			}
		}
	}
	
	void LoadTexCoords(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.texCoordsCount;

		if (mesh.texCoordsCount > 0)
		{
			mesh.texCoords = new TexCoord[mesh.texCoordsCount];

			for (int i = 0; i < mesh.texCoordsCount; i++)
			{
				inFile >> mesh.texCoords[i].u;
				inFile >> mesh.texCoords[i].v;
			}
		}
	}

	void LoadNormals(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.normalCount;

		if (mesh.normalCount > 0)
		{
			mesh.normals = new Vector3[mesh.normalCount];

			for (int i = 0; i < mesh.normalCount; i++)
			{
				inFile >> mesh.normals[i].x;
				inFile >> mesh.normals[i].y;
				inFile >> mesh.normals[i].z;
			}
		}
	}

	void LoadIndices(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.indexCount;
		mesh.indices = new GLushort[mesh.indexCount];

		for (int i = 0; i < mesh.indexCount; i++)
		{
			inFile >> mesh.indices[i];
		}
	}

	Mesh* MeshLoader::Load(char* path, bool loadTex, int size)
	{
		Mesh* mesh = new Mesh();

		mesh->size = size;

		ifstream inFile;

		inFile.open(path);

		if (!inFile.good())  
		{
			cerr  << "Can't open texture file " << path << endl;
			return nullptr;
		}

		LoadVertices(inFile, *mesh);
		//LoadColours(inFile, *mesh);
		if(loadTex)
			LoadTexCoords(inFile, *mesh);
		LoadNormals(inFile, *mesh);
		LoadIndices(inFile, *mesh);

		inFile.close();

		return mesh;
	}
	
}