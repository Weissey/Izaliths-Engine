#pragma once
#include <glew.h>
#include <glfw3.h>
#include <string>

class Shader {

private:

public:
		


	GLuint m_RendererID;
	GLuint GetRendererID() { return m_RendererID; }
	Shader() = default;
	~Shader();
	GLuint CompileShader(const std::string& vertPath, const std::string& fragPath);
	static Shader* createShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
};