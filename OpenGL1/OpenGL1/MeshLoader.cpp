#include "MeshLoader.h"

#include <iostream>
#include <fstream>

using namespace std;

namespace MeshLoader
{
	void LoadVertices(ifstream& inFile, Mesh& mesh);
	void LoadColours(ifstream& inFile, Mesh& mesh);
	void LoadTexCoords(ifstream& inFile, Mesh& mesh);
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
			}
		}
	}

	void LoadColours(ifstream& inFile, Mesh& mesh)
	{
		for (int i = 0; i < mesh.colourCount; i++)
		{
			inFile >> mesh.colours[i].r;
			inFile >> mesh.colours[i].g;
			inFile >> mesh.colours[i].b;
		}
	}

	void LoadTexCoords(ifstream& inFile, Mesh& mesh)
	{
		mesh.texCoords = new TexCoord[mesh.texCoordsCount];

		for (int i = 0; i < mesh.texCoordsCount; i++)
		{
			inFile >> mesh.texCoords[i].u;
			inFile >> mesh.texCoords[i].v;
		}
	}

	void LoadIndices(ifstream& inFile, Mesh& mesh)
	{
		mesh.indices = new GLushort[mesh.indexCount];

		for (int i = 0; i < mesh.indexCount; i++)
		{
			inFile >> mesh.indices[i];
		}
	}

	Mesh* MeshLoader::Load(char* path)
	{
		Mesh* mesh = new Mesh();

		ifstream inFile;

		inFile.open(path);

		if (!inFile.good())  
		{
			cerr  << "Can't open texture file " << path << endl;
			return nullptr;
		}

		LoadVertices(inFile, *mesh);
		LoadColours(inFile, *mesh);
		LoadIndices(inFile, *mesh);

		inFile.close();

		return mesh;
	}
	
}