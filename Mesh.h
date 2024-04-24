#pragma once
#include "Vertex.h"
#include <vector>

class Mesh
{
public:


	Mesh();
	~Mesh();

	std::vector<float> vertices;
	std::vector<uint32_t> indices;



private:

};

Mesh::Mesh()
{

}

Mesh::~Mesh()
{
}