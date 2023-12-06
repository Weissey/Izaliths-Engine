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

    Sprite* player = renderer.CreateSprite(Vec3<float>(600.0f, 600.0f, 0.0f), Vec2<float>(100.0f, 100.0f), Vec4<float>(1.0f, 1.0f, 0.0f, 1.0f));

    Sprite* g_collider = renderer.CreateSprite(Vec3<float>(0.0f, 0.0f, 0.0f), Vec2<float>(100.0f, 10.0f), Vec4<float>(1.0f, 0.0f, 1.0f, 1.0f));

    Sprite* h_collider = renderer.CreateSprite(Vec3<float>(0.0f, 0.0f, 0.0f), Vec2<float>(100.0f, 10.0f), Vec4<float>(1.0f, 0.0f, 1.0f, 1.0f));


    Sprite* ground = renderer.CreateSprite(Vec3<float>(600.0f, 0.0f, 0.0f), Vec2<float>(1200.0f, 100.0f), Vec4<float>(1.0f, 0.5f, 0.5f, 1.0f));

    Sprite* platforms[7];

    for (size_t i = 0; i < 7; i++)
    {
        platforms[i] = renderer.CreateSprite(Vec3<float>(50 + (rand() % 1150), 400 + (rand() % 800), 0.0f), Vec2<float>(200.0f, 50.0f), Vec4<float>(1.0f, 0.5f, 0.5f, 1.0f));
    }

    Vec3<float> velocity(0.0f, 0.0f, 0.0f);

    while (window.Update()) {
        nbFrames++;
        renderer.render();
        renderer.setUniformMat4("pr_matrix", ortho);

        g_collider->m_position.set(player->m_position.x, player->m_position.y - player->m_size.y / 2 + g_collider->m_size.y / 2, player->m_position.z);
        h_collider->m_position.set(player->m_position.x, player->m_position.y + player->m_size.y / 2 - g_collider->m_size.y / 2, player->m_position.z);


        if (g_collider->isBoxTouching(*ground)) {

            velocity.y = 0.0f;
        }

        for (size_t i = 0; i < 7; i++)
        {
            if (g_collider->isBoxTouching(*platforms[i])) {

                velocity.y = 0.0f;
            }

            if (h_collider->isBoxTouching(*platforms[i])) {

                velocity.y += -700.8f;
            }
        }


        
        if (window.key(GLFW_KEY_A)) {
            velocity.x = -200.0f;
        }
        else if (window.key(GLFW_KEY_D)) {
            velocity.x = 200.0f;
        }
        else {
            velocity.x = 0.0f;
        }

        bool grounded = false;

        for (size_t i = 3; i < renderer.spriteList.size(); i++)
        {
            if (player->isBoxTouching(*renderer.spriteList[i])) {
                grounded = true;
            }
        }
        
        if (window.key(GLFW_KEY_W) && grounded) {
            std::cout << "t" << std::endl;
            velocity.y = 900.0f;
        }


        player->m_position.y += velocity.y * window.deltaTime();
        player->m_position.x += velocity.x * window.deltaTime();

        velocity.y += -700.8f * window.deltaTime();

        if (window.currentTime - lastTime >= 1.0) {
            // Calculate frames per second and reset timer
            double fps = double(nbFrames) / (window.currentTime - lastTime);
            printf("%f fps\n", fps);

            nbFrames = 0;
            lastTime += 1.0;
        }

        //renderer.spriteList[0]->m_position.set(renderer.x, 0.0f, 0.0f);
        //renderer.setUniformMat4("ml_matrix", mat4::translation(Vec3<float>(renderer.y, 0, 0)));
        //player2->m_position.set(renderer.x, player2->m_position.y, 0.0f);


        window.render();
    }

    return 0;
}