#include "Object.h"
#include "Texture2D.h"
#include <sstream>
#define _USE_MATH_DEFINES
#include <math.h>

Object::Object(std::string _name, const char* _fileName, Object* _parent, Rotation* _rotation, Orbit* _orbit, GLfloat _scale, Vector4* _emission)
{
	hasNormals = false;
	hasTexture = false;

	name = _name;
	fileName = _fileName;
	
	parent = _parent;
	orbit = _orbit;
	rotation = _rotation;
	scale = _scale;

	emission = _emission;

	//If parent exists, set object position to parent. Offset dealt with later
	if (parent != nullptr)
		position = parent->position;
	//Set to center, as this is the parent
	else
	{
		position.x = 0;
		position.y = 0;
		position.z = 0;
	}
}

Object::~Object()
{ 
}

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

	//Read each line
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
			//n3 == -1 ? 3 : 4 determines if the face has 3 or 4 edges
			faces.push_back(Face(currentMat, n3 == -1 ? 3 : 4, v, t, n));
		}
		else if (line[0] == 'u' && line[1] == 's' && line[2] == 'e')
		{
			char tmp[200];
			sscanf_s(line.c_str(), "usemtl %s", &tmp, sizeof(tmp));  //read the name of the material to tmp
			for (int i = 0; i < materials.size(); i++) //go through all of the materials
			{
				if (strcmp(materials[i].name.c_str(), tmp) == 0) //compare value in tmp to the material name
				{
					currentMat = i; //Set current material to this material
					break;
				}
			}
		}
		//Get the material mtllib file - for material/texture
		else if (line[0] == 'm' && line[1] == 't' && line[2] == 'l' && line[3] == 'l')
		{
			char filen[200];
			sscanf_s(line.c_str(), "mtllib %s", filen, sizeof(filen));
			std::ifstream mtlin(filen);
			
			if (!mtlin.is_open())
			{
				std::cout << "connot open the material file" << std::endl;
				return;
			}

			std::vector<std::string> line;
			char c[200];
			
			while (!mtlin.eof())
			{
				mtlin.getline(c, 200); //read all lines to tmp
				line.push_back(c);
			}

			char nameChars[200];
			std::string matName;
			char filename[200];

			Vector4* amb = new Vector4(), *spec = new Vector4(), *dif = new Vector4();
			GLfloat ns = 0;

			unsigned int texture;
			bool ismat = false;

			strcpy_s(filename, "\0");

			for (std::string &line : line)
			{
				//If line commented out, continue
				if (line[0] == '\\' || line[0] == '//')
					continue;

				if (line[0] == 'n' && line[1] == 'e' && line[2] == 'w') //Creates name of new material
				{
					sscanf_s(line.c_str(), "newmtl %s", &nameChars, sizeof(nameChars));
				}
				else if (line[0] == 'N' && line[1] == 's') //Shininess
				{
					sscanf_s(line.c_str(), "Ns %f", &ns);
					ismat = true;
				}
				else if (line[0] == 'K' && line[1] == 'a') //Ambient
				{
					sscanf_s(line.c_str(), "Ka %f %f %f", &amb->x, &amb->y, &amb->z);
					amb->z = 0;
					ismat = true;
				}
				else if (line[0] == 'K' && line[1] == 'd') //Diffuse
				{
					sscanf_s(line.c_str(), "Kd %f %f %f", &dif->x, &dif->y, &dif->z);
					dif->w = 0;
					ismat = true;
				}
				else if (line[0] == 'K' && line[1] == 's') //Specular
				{
					sscanf_s(line.c_str(), "Ks %f %f %f", &spec->x, &spec->y, &spec->z);
					spec->z = 0;
					ismat = true;
				}
				else if (line[0] == 'm' && line[1] == 'a') //Texture
				{
					sscanf_s(line.c_str(), "map_Kd %s", filename, sizeof(nameChars));
					texture = LoadTexture(filename);
					ismat = true;
				}
			}
			//If material exists
			if (ismat) 
			{
				//Set material name
				for (char chars : nameChars)
				{
					if (chars == '\0')
						break;
					matName += chars;
				}

				//Create new material and push it onto the vector
				if (strcmp(filename, "\0") != 0)
				{
					Material* material = new Material();
					material->name = matName;
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

	//List of executions, with int name list
	list = glGenLists(1);
	glNewList(list, GL_COMPILE);

	bool hasMaterials = false;

	//If no materials, don't show any
	if (materials.size() == 0)
		hasMaterials = false;
	//Set program to show material
	else
		hasMaterials = true;

	int last = -1;

	for (Face& face : faces)
	{
		if (last != face.currentMat && hasMaterials)
		{
			//Sets all material components
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
			last = face.currentMat;

			if (materials[face.currentMat].texture == -1)
				glDisable(GL_TEXTURE_2D);
			else {
				glBindTexture(GL_TEXTURE_2D, materials[face.currentMat].texture);
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
	glEndList();

	//Clears vectors
	for (float* v : vertices)
		delete v;
	vertices.clear();
	for (float* t : texCoords)
		delete t;
	texCoords.clear();
	for (float* n : normals)
		delete n;
	normals.clear();

	materials.clear();
	faces.clear();

	lists.push_back(list);
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

		glCallList(list);
	}
	glPopMatrix();

	if (parent != nullptr)
		OrbitPath(500);
}

void Object::Update(bool isSpedUp)
{
	if (parent != nullptr)
		OrbitPosition(isSpedUp);

	//Rotate at the correct speed
	if(isSpedUp)
		rotation->rotation += rotation->increment * 4;
	else
		rotation->rotation += rotation->increment;

	//Reset if greater than 360
	if (rotation->rotation >= 360.0f)
		rotation->rotation = 0.0f;
}

void Object::OrbitPosition(bool isSpedUp)
{
	//Set horizontal angle around parent, with speed (depending on if normal or sped up)
	if(isSpedUp)
		orbit->horizontalAngle = fmod(orbit->horizontalAngle + orbit->speed * 4, M_PI * 2.0f);
	else	
		orbit->horizontalAngle = fmod(orbit->horizontalAngle + orbit->speed, M_PI * 2.0f);

	//Set positions
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

	//Gets positions of each vertex point on circle around parent object
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

	//Draws circle
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