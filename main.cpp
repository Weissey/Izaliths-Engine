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

    Renderer renderer;

    mat4 ortho = mat4::orthographic(0.0f, window.g_width(), 0.0f, window.g_height(), -1.0f, 1.0f);


    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

    mat4 perspective = mat4::perspective(45.0f, 1200.0f / 900.0f, 0.1f, 100.0f);
    //glEnable(GL_DEBUG_OUTPUT);
    //glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    //glDebugMessageCallback(debugCallback, nullptr);

    double lastTime = glfwGetTime();
    int nbFrames = 0;

    
    Sprite* cat = renderer.LoadOBJ("first", Vec3<float>(0.0f, 0.0f, 0.0f), Vec3<float>(20.0f, 20.0f, 20.0f), "cube.obj");

    Sprite* cat1 = renderer.LoadOBJ("first", Vec3<float>(20.0f, 0.0f, 0.0f), Vec3<float>(20.0f, 20.0f, 20.0f), "cube.obj");

    Sprite* cat2 = renderer.LoadOBJ("first", Vec3<float>(30.0f, 0.0f, 0.0f), Vec3<float>(20.0f, 20.0f, 20.0f), "cube.obj");

    Sprite* cube = renderer.CreateSprite("first", Vec3<float>(10.0f, 0.0f, 0.0f), Vec3<float>(1.0f, 50.0f, 50.0f), Vec4<float>(1.0f, 1.0f, 0.0f, 1.0f));
    
    Vec3<float> x(-36.0f, 10.0f, -117.0f);
    Vec3<float> y(0.0f, 0.0f, 0.0f);

    FPScam fps(Vec3<float>(0.0f, 0.0f, 0.0f), Vec3<float>(0.0f, 0.0f, 0.0f), window);

    Camera camera1(x, y);

    bool fps_on = true;

    while (window.Update()) {
        renderer.render();

        nbFrames++;

        if (window.currentTime - lastTime >= 1.0) {
            // Calculate frames per second and reset timer
            double fps = double(nbFrames) / (window.currentTime - lastTime);
            printf("%f fps\n", fps);

            nbFrames = 0;
            lastTime += 1.0;
        }


        if (window.keyPressed(GLFW_KEY_Q)) {
            fps_on = !fps_on;
        }

        if (window.keyPressed(GLFW_KEY_E)) {

            Sprite* cat = renderer.LoadOBJ("first", Vec3<float>(window.currentTime * 15.0f, 0.0f, 0.0f), Vec3<float>(20.0f, 20.0f, 20.0f), "cube.obj");
            std::cout << renderer.vertexCount << std::endl;
            std::cout << renderer.spriteList.size() << std::endl;
        }

        renderer.setUniformMat4("pr_matrix", perspective);

        if (fps_on) {
            renderer.setActiveCamera(fps);
        }
        else {
            renderer.setActiveCamera(camera1);
        }

    }

    return 0;
}