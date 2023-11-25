#pragma once
#include "glfw3.h"
#include "Maths.h"

struct Vertex
{
    Vec3<int> location;
    Vec4<int> color;
};

class Object
{
public:
	GLfloat vertices[9];
	Object();
	~Object();

	GLfloat* GetList();

private:

};