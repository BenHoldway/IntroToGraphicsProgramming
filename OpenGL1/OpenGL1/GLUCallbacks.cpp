#include "GLUTCallbacks.h"
#include "HelloGL.h"

namespace GLUTCallbacks
{
	namespace
	{
		//Initialise to a null pointer before we do anything
		HelloGL* helloGL = nullptr;
	}

	void Init(HelloGL* gl)
	{
		helloGL = gl;
	}

	void Display()
	{
		if (helloGL != nullptr)
			helloGL->Display();
	}

	void Timer(int preferredRefresh)
	{
		int updateTime = glutGet(GLUT_ELAPSED_TIME);
		helloGL->Update();
		updateTime -= glutGet(GLUT_ELAPSED_TIME);
		glutTimerFunc(preferredRefresh - updateTime, GLUTCallbacks::Timer, preferredRefresh);
	}

	void KeyboardDown(unsigned char key, int x, int y)
	{
		helloGL->KeyboardDown(key, x, y);
	}

	void KeyboardUp(unsigned char key, int x, int y)
	{
		helloGL->KeyboardUp(key, x, y);
	}

	void MouseMovement(int x, int y)
	{
		helloGL->MouseMovement(x, y);
	}

	void CreateMenu(int val)
	{
		helloGL->ObjectSelect(val);
	}
}