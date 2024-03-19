#pragma once

class HelloGL;

namespace GLUTCallbacks
{
	void Init(HelloGL* gl);
	void Display();
	void Timer(int preferredRefresh);
	void glutKeyboardFunc(unsigned char key, int x, int y);
	void glutKeyboardUpFunc(unsigned char key, int x, int y);
}
