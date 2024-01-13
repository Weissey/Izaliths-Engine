#pragma once
#include <glew.h>
#include <glfw3.h>
#include "Shader.h"
#include "Maths.h"
#include <array>
#include "sprite.h"
#include "camera.h"



class Renderer {

public:
	static const size_t MaxQuadCount = 100000;
	static const size_t MaxVertexCount = MaxQuadCount * 4;
	static const size_t MaxIndexCount = MaxQuadCount * 6;



	Renderer();
	~Renderer();

	uint32_t vertexCount = 0;
	uint32_t indexCount = 0;

	std::array<Vertex, MaxQuadCount> vertices;
	uint32_t indices[MaxIndexCount];

	//Vertex* vertices;
	//uint32_t* indices;

	Vertex* buffer;

	void compileVertices(Sprite* sprite);
	void compileIndices(Sprite* sprite);

	Sprite* CreateSprite(std::string name, Vec3<float> position, Vec3<float> size, Vec4<float> color);

	Sprite* LoadOBJ(std::string name, Vec3<float> position, Vec3<float> size, const char* filepath);

	void setActiveCamera(Camera& camera);
	void setActiveCamera(FPScam& camera);

	std::vector<Transform> transformStack;

	void setProjectionMatrix(const mat4& matrix);


	void setUniformMat4(const GLchar* name, const mat4& matrix);
	void setVec4(const GLchar* name, const Vec4<float>& color);
	void setVec3(const GLchar* name, const Vec3<float>& color);

	void rotateVertex(Vec3<float>& vertex, const Vec3<float>& center, const Vec3<float>& euler);

	Shader* m_Shader;
	void render();
	
	std::vector<Sprite*> spriteList;

private:
	void ImguiCode();
	GLuint m_SpriteVA;
	GLuint m_SpriteVB;
	GLuint m_SpriteIB;
	

};