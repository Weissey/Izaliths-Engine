#pragma once
#include <glew.h>
#include <glfw3.h>
#include "Shader.h"
#include "Maths.h"
#include <array>
#include "sprite.h"
#include "camera.h"
#include "Buffer.h"
#include "circleBuffer.h"


class Renderer {

public:
	const GLbitfield flags = GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT;


	static const size_t MaxQuadCount = 100000;
	static const size_t MaxVertexCount = MaxQuadCount * 4;
	static const size_t MaxIndexCount = MaxQuadCount * 10;

	uint32_t vertexCount = 0;
	uint32_t indexCount = 0;


	Renderer();
	~Renderer();

	uint32_t numBuffers = 3;
	uint32_t TbufferIndex = 0;
	circularBuffer<Buffer>* circleBuffer;

	std::vector<Sprite*> sprites;

	Vertex* vertices;
	uint32_t* indices;
	GLuint vao;

	Shader* m_Shader;

	void setProjectionMatrix(const mat4& matrix);

	void initBuffer();

	void updateBuffer(int bufferIndex);
	void mapBuffer(int bufferIndex);
	void unmapBuffer(int bufferIndex);

	Sprite* LoadOBJ(std::string name, Vec3<float> position, Vec3<float> size, const char* filepath);

	void render();
};