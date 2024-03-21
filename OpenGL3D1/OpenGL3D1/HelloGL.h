#pragma once

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"

#define REFRESHRATE 16


class HelloGL
{
public:

	struct point3D
	{
		float x;
		float y;
		float z;
	};

	struct colour
	{
		float r;
		float g;
		float b;
		colour(float _r, float _g, float _b)
		{
			r = _r;
			g = _g;
			b = _b;
		}
	};

	struct polygon
	{
		int a;
		int b;
		int c;
		int d;
		polygon(int _a, int _b, int _c, int _d)
		{
			a = _a;
			b = _b;
			c = _c;
			d = _d;
		}
	};

	point3D* vertices;
	colour* colours;
	polygon* indices;

	//constructor Definition
	HelloGL(int argc, char* argv[]);

	//Destructor
	~HelloGL(void);

	void Display();
	void Update();

	void DrawPolygon(int a, int b, int c, int d);
	void DrawCube();
};

