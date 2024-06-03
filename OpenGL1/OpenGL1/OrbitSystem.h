#pragma once
#include "Object.h"

#define NUMOBJECTS 7

class OrbitSystem
{
private:
	bool isSpedUp;
public:
	OrbitSystem();
	~OrbitSystem();
	void Draw();
	void Update();

	Object* objects[NUMOBJECTS];

	void SetIsSpedUp(bool value) { isSpedUp = value; }
};