#pragma once
#include <glew.h>
#include <glfw3.h>
#include "Shader.h"
#include "Maths.h"
#include <array>
#include "sprite.h"



class Renderer {

public:
	void start();

public:
	static const size_t MaxQuadCount = 10000;
	static const size_t MaxVertexCount = MaxQuadCount * 4;
	static const size_t MaxIndexCount = MaxQuadCount * 6;

	Renderer();
	uint32_t indexCount;
	std::array<Vertex, MaxQuadCount> vertices;
	Vertex* buffer;

	void CreateSquare(float x, float y);

	void addBuffers(const Sprite* sprite);
	Sprite* CreateSprite(Vec3<float> position, Vec2<float> size, Vec4<float> color);

	void setUniformMat4(const GLchar* name, const mat4& matrix);

	bool projection_type = false; //2d default


	Shader* m_Shader;
	void render();
	
	std::vector<Sprite*> spriteList;

private:
	void ImguiCode();
	GLuint m_SpriteVA;
	GLuint m_SpriteVB;
	GLuint m_SpriteIB;

private:

};