#include "Texture2D.h"
#include <stdio.h>
#define INVALID_FORMAT 0x4D42

Texture2D::Texture2D()
{

}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &ID);
}

//RAW file Loader
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

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	delete[] tempTextureData;
	return true;
}


//BMP File Loader
bool Texture2D::BMPLoad(char* path)
{
    unsigned char* tempTextureData;
    int fileSize;
    BITMAPFILEHEADER bmpFileHeader;
    BITMAPINFOHEADER bmpInfoHeader;

    //Was using std::ifstream, but couldn't figure out how to use that with BMP images
    FILE* inFile;
    //Reads file in binary
    fopen_s(&inFile, path, "rb");

    //If file not found
    if (!inFile)
    {
        std::cerr << "Can't open texture file " << path << std::endl;
        return false;
    }

    //Gets how many bytes were read from the file
    fread(&bmpFileHeader, sizeof(BITMAPFILEHEADER), 1, inFile);
    //Format is invalid
    if (bmpFileHeader.bfType != INVALID_FORMAT)
    {
        std::cerr << "Invalid file " << path << std::endl;
        return false;
    }

    //Gets image data, like size and colours
    fread(&bmpInfoHeader, sizeof(BITMAPINFOHEADER), 1, inFile);

    //If image size not got, set it manually
    if (bmpInfoHeader.biSizeImage == 0)
        bmpInfoHeader.biSizeImage = bmpInfoHeader.biHeight * bmpInfoHeader.biWidth * 3;

    tempTextureData = new unsigned char[bmpInfoHeader.biSizeImage];

    fseek(inFile, bmpFileHeader.bfOffBits, SEEK_SET);
    fread(tempTextureData, 1, bmpInfoHeader.biSizeImage, inFile);

    unsigned char temp;

    for (int i = 0; i < bmpInfoHeader.biSizeImage - 2; i += 3)
    {
        temp = tempTextureData[i];
        tempTextureData[i] = tempTextureData[i + 2];
        tempTextureData[i + 2] = temp;
    }

    fclose(inFile);

    //Generates and sets texture to use
    width = bmpInfoHeader.biWidth;
    height = bmpInfoHeader.biHeight;

    glGenTextures(1, &ID);

    glBindTexture(GL_TEXTURE_2D, ID);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, bmpInfoHeader.biWidth, bmpInfoHeader.biHeight, GL_RGB, GL_UNSIGNED_BYTE, tempTextureData);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    delete[] tempTextureData;
    return true;
}