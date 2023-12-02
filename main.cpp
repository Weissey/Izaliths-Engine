//#include <GL/glew.h>

#include <iostream>
#include <glew.h>
#include <glfw3.h>
#include "Window.h"
#include "Renderer.h"
#include <vector>


void GLAPIENTRY debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    // Print or log the debug message
    std::cerr << "OpenGL Debug Message: " << message << std::endl;
}



int main() {

    Window window(1200, 1200, "Oolong", false);

    Renderer renderer;
    renderer.start();

    mat4 ortho = mat4::orthographic(0.0f, window.g_width(), 0.0f, window.g_height(), -1.0f, 1.0f);


    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

    //mat4 perspective = mat4::perspective(45.0f, 16 / 9.0f, 0.1f, 100.0f);
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(debugCallback, nullptr);

    double lastTime = glfwGetTime();
    int nbFrames = 0;

    Vec3<float> pos(600.0f, 600.0f, 0.0f);
    Sprite* player = renderer.CreateSprite(pos, Vec2<float>(100.0f, 100.0f), Vec4<float>(1.0f, 1.0f, 0.0f, 1.0f));

    //Sprite* player2 = renderer.CreateSprite(Vec3<float>(300.0f, 300.0f, 0.0f), Vec2<float>(100.0f, 100.0f), Vec4<float>(1.0f, 0.0f, 1.0f, 1.0f));



    while (window.Update()) {
        double currentTime = glfwGetTime();
        nbFrames++;

        if (currentTime - lastTime >= 1.0) {
            // Calculate frames per second and reset timer
            double fps = double(nbFrames) / (currentTime - lastTime);
            printf("%f fps\n", fps);

            nbFrames = 0;
            lastTime += 1.0;
        }

        renderer.render();

        renderer.setUniformMat4("pr_matrix", ortho);

        if (window.key(GLFW_KEY_W)) {
            std::cout << "W pressed" << std::endl;
            pos.y++;
        }
        if (window.key(GLFW_KEY_A)) {
            std::cout << "A pressed" << std::endl;
            pos.x--;
        }
        if (window.key(GLFW_KEY_S)) {
            std::cout << "S pressed" << std::endl;
            pos.y--;
        }
        if (window.key(GLFW_KEY_D)) {
            std::cout << "D pressed" << std::endl;
            pos.x++;
        }
        player->m_position.set(pos.x, pos.y, pos.z);


        //renderer.spriteList[0]->m_position.set(renderer.x, 0.0f, 0.0f);
        //renderer.setUniformMat4("ml_matrix", mat4::translation(Vec3<float>(renderer.y, 0, 0)));
        //player2->m_position.set(renderer.x, player2->m_position.y, 0.0f);

        window.render();
    }

    return 0;
}