#include "OrbitSystem.h"

OrbitSystem::OrbitSystem()
{
	Vector4* starEmission = new Vector4();
	starEmission->x = 0.5f; starEmission->y = 0.5f; starEmission->z = 0.5f; starEmission->w = 0.0f;

	//Star
	objects[0] = new Object(
		"Urexia 5b",
		(char*)"Objects/Urexia-5b.obj", //Object File
		nullptr, //Parent Object
		new Rotation(0.5f, 0.3f, 0.0f, 5.0f, 0.5f), //Rotation values; x, y, z, rotation Val, increment
		new Orbit(0, 0, 0), //Orbit values; speed, radius, horizontal angle
		2,
		starEmission
	);

	//Planet 1
	objects[1] = new Object(
		"Naheme",
		(char*)"Objects/Naheme.obj",
		objects[0],
		new Rotation(0.0f, 0.2f, 0.0f, 0.5f, 0.25f),
		new Orbit(0.005f, 10.0f, 0),
		0.4,
		nullptr
	);

	//Planet 2
	objects[2] = new Object(
		"Churater",
		(char*)"Objects/Churater.obj",
		objects[0],
		new Rotation(0.0f, 0.2f, 0.2f, 0.5f, 0.25f),
		new Orbit(0.001, 30.0f, 0),
		1.6,
		nullptr
	);

	objects[3] = new Object(
		"Vipaha 30", 
		(char*)"Objects/Vipaha-30.obj",
		objects[0],
		new Rotation(0.2f, 0.8f, 0.2f, 0.3f, 0.18f),
		new Orbit(0.002, 40.0f, 0),
		1.6,
		nullptr
	);

	//objects[4] = new Object(
	//	"Oclepe",
	//	(char*)"Objects/Oclepe.obj",
	//	objects[0],
	//	new Rotation(0.2f, 0.8f, 0.2f, 0.3f, 0.18f),
	//	new Orbit(0.0004, 80.0f, 0),
	//	1.6,
	//	nullptr
	//);

	//objects[5] = new Object(
	//	"Gerutha",
	//	(char*)"Objects/Gerutha.obj",
	//	objects[0],
	//	new Rotation(0.2f, 0.8f, 0.2f, 0.3f, 0.18f),
	//	new Orbit(0.0003, 100.0f, 0),
	//	1.6,
	//	nullptr
	//);

	//objects[6] = new Object(
	//	"Pheromos 9",
	//	(char*)"Objects/Pheromos-9.obj",
	//	objects[0],
	//	new Rotation(0.2f, 0.8f, 0.2f, 0.3f, 0.18f),
	//	new Orbit(0.0008, 130.0f, 0),
	//	1.6,
	//	nullptr
	//);
}

OrbitSystem::~OrbitSystem()
{
}

void OrbitSystem::Draw()
{
	for (Object* object : objects)
	{
		if (object == nullptr)
			break;
		
		object->Draw();
	}
}

void OrbitSystem::Update()
{
	for (Object* object : objects)
	{
		if (object == nullptr)
			break;

		object->Update();
	}
}
