#pragma once
#include <glew.h>
#include <glfw3.h>
#include "Shader.h"
#include "Maths.h"
#include <array>


struct Vertex {
	Vec3<float> position;
	Vec4<float> color;
};


class Renderer {

public:
	void start();

public:
	const size_t quadcount = 10000;
	const size_t vertcount = quadcount * 4;
	const size_t indexcount = quadcount * 6;

	uint32_t indexCount;
	std::array<Vertex, 1000> vertices;
	Vertex* buffer;

	void CreateSquare(float x, float y);

	Renderer();
	Shader* m_Shader;
	void render();
	

private:
	void ImguiCode();
	GLuint m_SpriteVA;
	GLuint m_SpriteVB;
	GLuint m_SpriteIB;


};