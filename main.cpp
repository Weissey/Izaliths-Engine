//#include <GL/glew.h>

#include <iostream>
#include <glew.h>
#include <glfw3.h>
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

    Window window(2400, 1200, "Oolong", false);

    Renderer renderer;
    renderer.start();

    mat4 ortho = mat4::orthographic(0.0f, window.g_width(), 0.0f, window.g_height(), -1.0f, 1.0f);


    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

    mat4 perspective = mat4::perspective(45.0f, 1200.0f / 900.0f, 0.1f, 100.0f);
    //glEnable(GL_DEBUG_OUTPUT);
    //glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    //glDebugMessageCallback(debugCallback, nullptr);

    double lastTime = glfwGetTime();
    int nbFrames = 0;

    Vec3<float> camera_pos(0, 0, 0);
    Vec3<float> camera_look(0, 0, 0);

    float movespeed = 15.0f;

    float lookspeed = 5.0f;

    Sprite* ground1 = renderer.CreateSprite("first", Vec3<float>(15.0f, -7.0f, -40.0f), Vec3<float>(5.0f, 5.0f, 5.0f), Vec4<float>(1.0f, 1.0f, 0.0f, 1.0f));
    Sprite* ground2 = renderer.CreateSprite("first", Vec3<float>(-15.0f, -11.0f, -40.0f), Vec3<float>(5.0f, 5.0f, 5.0f), Vec4<float>(1.0f, 1.0f, 0.0f, 1.0f));
    Sprite* ground3 = renderer.CreateSprite("first", Vec3<float>(-4.0f, -10.0f, -40.0f), Vec3<float>(5.0f, 5.0f, 5.0f), Vec4<float>(1.0f, 1.0f, 0.0f, 1.0f));

    Sprite* ground4 = renderer.CreateSprite("first", Vec3<float>(-6.0f, 7.0f, -40.0f), Vec3<float>(5.0f, 5.0f, 5.0f), Vec4<float>(1.0f, 1.0f, 0.0f, 1.0f));

    Sprite* ground5 = renderer.CreateSprite("first", Vec3<float>(12.0f, 2.0f, -40.0f), Vec3<float>(5.0f, 5.0f, 5.0f), Vec4<float>(1.0f, 1.0f, 0.0f, 1.0f));


    while (window.Update()) {
        nbFrames++;
        renderer.render();

        ground1->rotate(Vec3<float>(window.currentTime * -25.0f, 0, 0));
        ground2->rotate(Vec3<float>(window.currentTime * 25.0f, 0, 0));
        ground3->rotate(Vec3<float>(window.currentTime * -25.0f, 0, 0));

        ground4->rotate(Vec3<float>(window.currentTime * -25.0f, 0, 0));
        ground5->rotate(Vec3<float>(window.currentTime * -25.0f, 0, 0));


        if (window.key(GLFW_KEY_W)) {
            camera_pos.z += movespeed * window.deltaTime();
        }

        if (window.key(GLFW_KEY_A)) {
            camera_pos.x += movespeed * window.deltaTime();
        }

        if (window.key(GLFW_KEY_S)) {
            camera_pos.z -= movespeed * window.deltaTime();
        }

        if (window.key(GLFW_KEY_D)) {
            camera_pos.x -= movespeed * window.deltaTime();
        }

        if (window.key(GLFW_KEY_LEFT)) {
            camera_look.y += lookspeed * window.deltaTime();
        }

        if (window.key(GLFW_KEY_RIGHT)) {
            camera_look.y -= lookspeed * window.deltaTime();
        }

        if (window.key(GLFW_KEY_UP)) {
            camera_look.x += lookspeed * window.deltaTime();
        }

        if (window.key(GLFW_KEY_DOWN)) {
            camera_look.x -= lookspeed * window.deltaTime();
        }

        renderer.setUniformMat4("pr_matrix", perspective);

        if (window.currentTime - lastTime >= 1.0) {
            // Calculate frames per second and reset timer
            double fps = double(nbFrames) / (window.currentTime - lastTime);
            printf("%f fps\n", fps);

            nbFrames = 0;
            lastTime += 1.0;
        }


        mat4 sum = mat4::translation(camera_pos) * mat4::rotation(camera_look);
        renderer.setUniformMat4("vw_matrix", sum);

        window.render();

    }

    return 0;
}