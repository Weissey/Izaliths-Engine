#pragma once
#include <glew.h>
#include <glfw3.h>
#include "Shader.h"
#include "Maths.h"
#include <array>
#include "sprite.h"



class Renderer {

public:
	static const size_t MaxQuadCount = 100000;
	static const size_t MaxVertexCount = MaxQuadCount * 4;
	static const size_t MaxIndexCount = MaxQuadCount * 6;



	Renderer();
	uint32_t vertexCount = 0;
	uint32_t indexCount = 0;

	//std::array<Vertex, MaxQuadCount> vertices;
	std::vector<Vertex> vertices;

	uint32_t indices[MaxIndexCount];

	Vertex* buffer;

	void addBuffers(const Sprite* sprite);

	Sprite* CreateSprite(std::string name, Vec3<float> position, Vec3<float> size, Vec4<float> color);

	Sprite* LoadOBJ(std::string name, Vec3<float> position, Vec3<float> size, const char* filepath);


	void setUniformMat4(const GLchar* name, const mat4& matrix);


	Shader* m_Shader;
	void render();
	
	std::vector<Sprite*> spriteList;

private:
	void ImguiCode();
	GLuint m_SpriteVA;
	GLuint m_SpriteVB;
	GLuint m_SpriteIB;

public:
	void setCamera(Vec3<float> pos);
	void TranslateCamera(Vec3<float> pos);
	void RotateCamera(Vec3<float> angles);

	Vec3<float> camera_pos;
	Vec3<float> camera_rotation;
	
	void rotateVertex(Vec3<float>& vertex, Vec3<float> center, Vec3<float> euler);

};