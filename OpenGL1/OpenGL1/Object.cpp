#include "Object.h"
#include "Texture2D.h"
#include <sstream>
#define _USE_MATH_DEFINES
#include <math.h>

Object::Object(std::string _name, const char* fileName, Object* _parent, Rotation* _rotation, Orbit* _orbit, GLfloat _scale, Vector4* _emission)
{
	hasNormals = false;
	hasTexture = false;

	name = _name;

	parent = _parent;
	
	orbit = _orbit;
	rotation = _rotation;

	scale = _scale;

	emission = _emission;

	if (parent != nullptr)
		position = parent->position;
	else
	{
		position.x = 0;
		position.y = 0;
		position.z = 0;
	}

	Load(fileName);
}

Object::~Object(){ }

void Object::Load(const char* filename)
{
	std::string line;
	std::vector<std::string> lines;

	std::ifstream inFile(filename);

	if (!inFile.good() || !inFile.is_open())
	{
		std::cerr << "Can't open texture file" << filename << std::endl;
		return;
	}

	while (!inFile.eof())
	{
		std::getline(inFile, line);
		lines.push_back(line);
	}

	inFile.close();

	std::cout << filename << " loaded." << std::endl;

	float part1, part2, part3;
	int currentMat = 0;

	for (std::string& line : lines)
	{
		if (line[0] == 'v') //If v, add to vertices
		{
			if (line[1] == ' ')
			{
				sscanf_s(line.c_str(), "v %f %f %f", &part1, &part2, &part3);
				vertices.push_back(new float[3] {part1, part2, part3});
			}
			else if (line[1] == 't') //If t, add to texture coordinates with 2 values
			{
				sscanf_s(line.c_str(), "vt %f %f", &part1, &part2);
				texCoords.push_back(new float[2] {part1, part2});
			}
			else if (line[1] == 'n') //If n, add to normals
			{
				sscanf_s(line.c_str(), "vn %f %f %f", &part1, &part2, &part3);
				normals.push_back(new float[3] {part1, part2, part3});
				hasNormals = true;
			}
			else //If t, add to texture coordinates with 3 values
			{
				sscanf_s(line.c_str(), "vt %f %f %f", &part1, &part2, &part3);
				texCoords.push_back(new float[3] {part1, part2, part3});
			}
		}
		else if (line[0] == 'f') //If f, create faces with vertices, normals and texture coordinates
		{
			int v0, v1, v2, v3, t0, t1, t2, t3, n0, n1, n2, n3 = -1;
			sscanf_s(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d", &v0, &t0, &n0, &v1, &t1, &n1, &v2, &t2, &n2, &v3, &t3, &n3);
			int* v = new int[4] {v0 - 1, v1 - 1, v2 - 1, v3 - 1};
			int* t = new int[4] {t0 - 1, t1 - 1, t2 - 1, t3 - 1};
			int* n = new int[4] {n0 - 1, n1 - 1, n2 - 1, n3 - 1};
			faces.push_back(Face(currentMat, n3 == -1 ? 3 : 4, v, t, n));
		}
		else if (line[0] == 'u' && line[1] == 's' && line[2] == 'e')
		{
			char tmp[200];
			sscanf_s(line.c_str(), "usemtl %s", &tmp, sizeof(tmp));  //read the name of the material to tmp
			for (int i = 0; i < materials.size(); i++) //go through all of the materials
			{
				if (strcmp(materials[i].name.c_str(), tmp) == 0)   //and compare the tmp with the name of the material
				{
					currentMat = i;   //if it's equal then set the current material to that
					break;
				}
			}
		}
		else if (line[0] == 'm' && line[1] == 't' && line[2] == 'l' && line[3] == 'l')
		{
			char filen[200];
			sscanf_s(line.c_str(), "mtllib %s", filen, sizeof(filen));    //read the filename
			std::ifstream mtlin(filen); //open the file
			
			if (!mtlin.is_open())    //if not opened error message, clean all memory, return with -1
			{
				std::cout << "connot open the material file" << std::endl;
				return;
			}

			//ismaterial = true;    //we use materials
			std::vector<std::string> line;//contain all of the line of the file
			char c[200];
			
			while (!mtlin.eof())
			{
				mtlin.getline(c, 200); //read all lines to tmp
				line.push_back(c);
			}

			char nameChars[200]; //name of the material
			std::string name;
			char filename[200]; //filename of the texture

			Vector4* amb = new Vector4(), *spec = new Vector4(), *dif = new Vector4();
			GLfloat ns = 0;

			unsigned int texture;
			
			bool ismat = false;   //do we already have a material read in to these variables?

			strcpy_s(filename, "\0");  //set filename to nullbyte character

			for (std::string &line : line)
			{
				if (line[0] == '\\')
					continue;

				if (line[0] == 'n' && line[1] == 'e' && line[2] == 'w')  //new material
				{
					sscanf_s(line.c_str(), "newmtl %s", &nameChars, sizeof(nameChars));
				}
				else if (line[0] == 'N' && line[1] == 's')  //the shininess
				{
					sscanf_s(line.c_str(), "Ns %f", &ns);
					ismat = true;
				}
				else if (line[0] == 'K' && line[1] == 'a')  //the ambient
				{
					sscanf_s(line.c_str(), "Ka %f %f %f", &amb->x, &amb->y, &amb->z);
					amb->z = 0;
					ismat = true;
				}
				else if (line[0] == 'K' && line[1] == 'd')  //the diffuse
				{
					sscanf_s(line.c_str(), "Kd %f %f %f", &dif->x, &dif->y, &dif->z);
					dif->w = 0;
					ismat = true;
				}
				else if (line[0] == 'K' && line[1] == 's')  //the specular
				{
					sscanf_s(line.c_str(), "Ks %f %f %f", &spec->x, &spec->y, &spec->z);
					spec->z = 0;
					ismat = true;
				}
				else if (line[0] == 'm' && line[1] == 'a')  //and the texture
				{
					sscanf_s(line.c_str(), "map_Kd %s", filename, sizeof(nameChars));
					texture = LoadTexture(filename);  //read the filename, and use the loadTexture function to load it, and getthe id.
					ismat = true;
				}
			}
			if (ismat)   //there is no newmat after the last newmat, so we have to put the last material 'manually'
			{
				for (char chars : nameChars)
				{
					if (chars == '\0')
						break;
					name += chars;
				}

				if (strcmp(filename, "\0") != 0)
				{
					Material* material = new Material();
					material->name = name;
					material->ambient = *amb;
					material->diffuse = *dif;
					material->specular = *spec;
					material->shininess = ns;
					material->texture = texture;

					material->emissive.x = 0.0f; material->emissive.y = 0.0f; material->emissive.z = 0.0f; material->emissive.w =0.0f;

					materials.push_back(*material);
				}
			}
		}
	}

	//for (float* v : vertices)
	//	delete v;
	//vertices.clear();
	//for (float* t : texCoords)
	//	delete t;
	//texCoords.clear();
	//for (float* n : normals)
	//	delete n;
	//normals.clear();

	//faces.clear();
}

unsigned int Object::LoadTexture(const char* fileName)
{
	Texture2D* texture = new Texture2D();
	texture->BMPLoad((char*)fileName);
	return texture->GetID();
}

void Object::Draw()
{
	glPushMatrix();
	{
		glTranslatef(position.x, position.y, position.z);
		glScalef(scale, scale, scale);
		glRotatef(rotation->rotation, rotation->rotX, rotation->rotY, rotation->rotZ);

		bool hasMaterials = false;

		if (materials.size() == 0) //if some reason the material file doesn't contain any material, we don't have material
			hasMaterials = false;
		else    //else we have
			hasMaterials = true;

		list = glGenLists(1);
		glNewList(list, GL_COMPILE);

		int last = -1;

		for (Face& face : faces)
		{
			if (last != face.currentMat && hasMaterials)   //if we have a meterial AND the last material is not the same
			{
				//set all of the material property
				float diffuse[] = {
					materials[face.currentMat].diffuse.x,
					materials[face.currentMat].diffuse.y,
					materials[face.currentMat].diffuse.z,
					1.0
				};
				float specular[] = {
					materials[face.currentMat].specular.x,
					materials[face.currentMat].specular.y,
					materials[face.currentMat].specular.z,
					1.0
				};

				float ambient[] = { 0, 0, 0, 0 };

				if (emission != nullptr)
				{
					float emissive[] = {
						materials[face.currentMat].emissive.x,
						materials[face.currentMat].emissive.y,
						materials[face.currentMat].emissive.z,
						1.0
					};
					glMaterialfv(GL_FRONT, GL_EMISSION, &emission->x);
				}
				else
				{
					ambient[0] = materials[face.currentMat].ambient.x;
					ambient[1] = materials[face.currentMat].ambient.y;
					ambient[2] = materials[face.currentMat].ambient.z;
					ambient[3] = 1.0;
				}

				glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
				glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
				glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
				glMaterialf(GL_FRONT, GL_SHININESS, materials[face.currentMat].shininess);
				last = face.currentMat; //set the current to last

				if (materials[face.currentMat].texture == -1)   //if we don't have texture, disable it, else enable it
					glDisable(GL_TEXTURE_2D);
				else {
					glBindTexture(GL_TEXTURE_2D, materials[face.currentMat].texture); //and use it
				}
			}

			if (face.normals)
				glEnable(GL_LIGHTING);
			if (face.texCoords)
				glEnable(GL_TEXTURE_2D);

			glBegin(GL_POLYGON);
			{
				for (int i = 0; i < face.edge; i++)
				{
					if (face.normals)
						glNormal3fv(normals[face.normals[i]]);
					if (face.texCoords)
						glTexCoord2fv(texCoords[face.texCoords[i]]);
					glVertex3fv(vertices[face.vertices[i]]);
				}
			}
			glEnd();
		}
	}
	glPopMatrix();

	glEndList();

	glCallList(list);

	if (parent != nullptr)
		OrbitPath(100);
}

void Object::Update()
{
	if (parent != nullptr)
		OrbitPosition();

	rotation->rotation += rotation->increment;

	if (rotation->rotation >= 360.0f)
		rotation->rotation = 0.0f;
}

void Object::OrbitPosition()
{
	orbit->horizontalAngle = fmod(orbit->horizontalAngle + orbit->speed, M_PI * 2.0f);

	position.x = parent->position.x + orbit->radius * cosf(orbit->horizontalAngle) * cosf(0);
	position.y = parent->position.y + orbit->radius * sinf(0);
	position.z = parent->position.z + orbit->radius * sinf(orbit->horizontalAngle) * cosf(0);
}

void Object::OrbitPath(GLint numberOfSides)
{
	GLint numOfVertices = numberOfSides + 1;
	GLfloat twoPi = 2.0f * M_PI;

	GLfloat *circleX = new GLfloat[numOfVertices];
	GLfloat *circleY = new GLfloat[numOfVertices];
	GLfloat *circleZ = new GLfloat[numOfVertices];

	for (int i = 0; i < numOfVertices; i++)
	{
		circleX[i] = parent->position.x + (orbit->radius * cos(i * twoPi / numberOfSides));
		circleY[i] = parent->position.y + (orbit->radius * sin(i * twoPi / numberOfSides));
		circleZ[i] = parent->position.z;
	}

	GLfloat *circleVertices = new GLfloat[numOfVertices * 3];

	for (int i = 0; i < numOfVertices; i++)
	{
		circleVertices[i * 3] = circleX[i];
		circleVertices[(i * 3) + 1] = circleY[i];
		circleVertices[(i * 3) + 2] = circleZ[i];
	}

	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_TEXTURE_2D);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, circleVertices);
	glPushMatrix();
		glRotatef(90, 1, 0, 0);
		glDrawArrays(GL_LINE_LOOP, 0, numOfVertices);
	glPopMatrix();
	glDisableClientState(GL_VERTEX_ARRAY);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_TEXTURE_2D);
}