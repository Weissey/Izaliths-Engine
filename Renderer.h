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

	const size_t quadcount = 10000;
	const size_t vertcount = quadcount * 4;
	const size_t indexcount = quadcount * 6;

	uint32_t indexCount;

	static Vertex* CreateSquare(Vertex* buffer, float x, float y);

	Renderer();
	Shader* m_Shader;
	void drawTriangle(int x, int y);
	void render();
	Vec3<float> pos;

	

private:
	void ImguiCode();
	GLuint m_SpriteVA;
	GLuint m_SpriteVB;
	GLuint m_SpriteIB;


};