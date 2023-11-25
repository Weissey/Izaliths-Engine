#pragma once
#include "Object.h"

class Scene
{
public:
	Scene();
	void CreateSprite();
	~Scene();

private:
	std::vector<GLfloat> all_vertices;
	std::vector<uint16_t> all_indices;
};

