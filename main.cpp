//#include <GL/glew.h>

#include <iostream>
#include "Window.h"
#include "Renderer.h"
#include "camera.h"
#include <vector>


void GLAPIENTRY debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    // Print or log the debug message
    std::cerr << "OpenGL Debug Message: " << message << std::endl;
}



int main() {

    Window window(1600, 1000, "Oolong", false);
    //window.setBackgroundColor(1.0f, 0.0f, 0.0f, 1.0f);


    Renderer renderer;

    mat4 ortho = mat4::orthographic(0.0f, window.g_width(), 0.0f, window.g_height(), -1.0f, 1.0f);


    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    

    mat4 perspective = mat4::perspective(45.0f, 1200.0f / 900.0f, 0.1f, 100.0f);
    //glEnable(GL_DEBUG_OUTPUT);
    //glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    //glDebugMessageCallback(debugCallback, nullptr);


    Sprite* cat = renderer.LoadOBJ("first", Vec3<float>(0.0f, 0.0f, 0.0f), Vec3<float>(20.0f, 20.0f, 20.0f), "cube.obj");
    
    Vec3<float> x(-36.0f, 10.0f, -117.0f);
    Vec3<float> y(0.0f, 0.0f, 0.0f);

    FPScam fps(Vec3<float>(0.0f, 0.0f, 0.0f), Vec3<float>(0.0f, 0.0f, 0.0f), window);

    Camera camera1(x, y);

    bool fps_on = true;

    while (window.Update()) {
        renderer.render();
        renderer.setProjectionMatrix(perspective); // high 90%

        for (size_t i = 0; i < renderer.spriteList.size(); i++)
        {
            renderer.spriteList[i]->setRotation(Vec3<float>(window.currentTime * 5.0f * i, window.currentTime * 5.0f * i, window.currentTime * 5.0f * i));
        }

        //cat->setRotation(Vec3<float>(0.0f, window.currentTime * 5.0f, window.currentTime * 5.0f));

        if (window.keyPressed(GLFW_KEY_Q)) {
            fps_on = !fps_on;
        }

        if (window.keyPressed(GLFW_KEY_E)) {

            Sprite* cat4 = renderer.LoadOBJ("first", Vec3<float>(window.currentTime * 9.0f, 0.0f, 0.0f), Vec3<float>(20.0f, 20.0f, 20.0f), "cube.obj");
            std::cout << renderer.vertexCount << std::endl;
            std::cout << renderer.spriteList.size() << std::endl;
        }


        if (fps_on) {
            renderer.setActiveCamera(fps);
        }
        else {
            renderer.setActiveCamera(camera1);
        }

    }

    return 0;
}