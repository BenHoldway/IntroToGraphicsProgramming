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
		helloGL->Update();
		glutTimerFunc(preferredRefresh, GLUTCallbacks::Timer, preferredRefresh);
	}

	void glutKeyboardFunc(unsigned char key, int x, int y)
	{
		if(key == 32)
			helloGL->isKeyDown = true;
	}

	void glutKeyboardUpFunc(unsigned char key, int x, int y)
	{
		helloGL->isKeyDown = false;
	}
}