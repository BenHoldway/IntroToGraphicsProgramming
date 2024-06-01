#include "Texture2D.h"

Texture2D::Texture2D()
{

}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &ID);
}

bool Texture2D::Load(char* path, int _width, int _height)
{
	char* tempTextureData;
	int fileSize;
	std::ifstream inFile;

	width = _width;
	height = _height;

	inFile.open(path, std::ios::binary);

	if (!inFile.good())
	{
		std::cerr << "Can't open texture file" << path << std::endl;
		return false;
	}

	//Go to end of file and get total size
	inFile.seekg(0, std::ios::end);
	fileSize = (int)inFile.tellg();
	tempTextureData = new char[fileSize];

	//Go back to beginning and read in all of the data
	inFile.seekg(0, std::ios::beg);
	inFile.read(tempTextureData, fileSize);

	inFile.close();

	std::cout << path << " loaded." << std::endl;

	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, tempTextureData);
	//gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, tempTextureData);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	delete[] tempTextureData;
	return true;
}