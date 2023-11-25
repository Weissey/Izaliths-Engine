//#include <GL/glew.h>

#include <iostream>
#include <glew.h>
#include <glfw3.h>
#include "Window.h"
#include "Renderer.h"
#include <vector>


void drawTriangle() {
    // Define vertices of a triangle
    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f,   // Vertex 1
         0.5f, -0.5f, 0.0f,   // Vertex 2
         0.0f,  0.5f, 0.0f    // Vertex 3
    };

    // Create and bind a vertex array object (VAO)
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Create a vertex buffer object (VBO)
    GLuint VBO;
    glGenBuffers(1, &VBO);

    // Bind VBO and copy vertex data to it
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Specify vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Draw the triangle
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);

    // Clean up
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}



void GLAPIENTRY debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    // Print or log the debug message
    std::cerr << "OpenGL Debug Message: " << message << std::endl;
}


Renderer renderer;
Window window(2600, 1300, "Oolong", false);

int main() {

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
    renderer.drawTriangle(45, 45);

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(debugCallback, nullptr);


    while (window.Update()) {


        renderer.render();
        window.render();
    }

    return 0;
}