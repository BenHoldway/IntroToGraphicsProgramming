#pragma once
#include "Object.h"

#define NUMOBJECTS 4

class OrbitSystem
{
private:
public:
	OrbitSystem();
	~OrbitSystem();
	void Draw();
	void Update();

	Object* objects[NUMOBJECTS];
};