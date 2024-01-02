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

    Vec3<float> camera_pos(0, 0, 0);
    Vec3<float> camera_look(0, 0, 0);

    float movespeed = 20.0f;

    float lookspeed = 40.0f;
    
    //Sprite* ground = renderer.CreateSprite("first", Vec3<float>(0.0f, -10.0f, 0.0f), Vec3<float>(50.0f, 5.0f, 50.0f), Vec4<float>(1.0f, 1.0f, 0.0f, 1.0f));

    //Sprite* wall1 = renderer.CreateSprite("first", Vec3<float>(0.0f, -10.0f, 25.0f), Vec3<float>(50.0f, 10.0f, 5.0f), Vec4<float>(1.0f, 1.0f, 0.0f, 1.0f));
    //Sprite* wall2 = renderer.CreateSprite("first", Vec3<float>(-25.0f, -10.0f, 0.0f), Vec3<float>(5.0f, 10.0f, 50.0f), Vec4<float>(1.0f, 1.0f, 0.0f, 1.0f));
    //Sprite* wall3 = renderer.CreateSprite("first", Vec3<float>(0.0f, -10.0f, -25.0f), Vec3<float>(50.0f, 10.0f, 5.0f), Vec4<float>(1.0f, 1.0f, 0.0f, 1.0f));
    //Sprite* wall4 = renderer.CreateSprite("first", Vec3<float>(25.0f, -10.0f, 0.0f), Vec3<float>(5.0f, 10.0f, 50.0f), Vec4<float>(1.0f, 1.0f, 0.0f, 1.0f));


    //Sprite* cube = renderer.CreateSprite("first", Vec3<float>(10.0f, 0.0f, 0.0f), Vec3<float>(50.0f, 50.0f, 50.0f), Vec4<float>(1.0f, 1.0f, 0.0f, 1.0f));


    Sprite* cat = renderer.LoadOBJ("first", Vec3<float>(0.0f, 0.0f, 0.0f), Vec3<float>(20.0f, 20.0f, 20.0f), "cube.obj");

    Sprite* cat1 = renderer.LoadOBJ("first", Vec3<float>(20.0f, 0.0f, 0.0f), Vec3<float>(20.0f, 20.0f, 20.0f), "cube.obj");

    Sprite* cat2 = renderer.LoadOBJ("first", Vec3<float>(30.0f, 0.0f, 0.0f), Vec3<float>(20.0f, 20.0f, 20.0f), "cube.obj");


    //Sprite* cat2 = renderer.LoadOBJ("second", Vec3<float>(10.0f, 0.0f, 0.0f), Vec3<float>(1.0f, 1.0f, 1.0f), "cat.obj");


    Sprite* cube = renderer.CreateSprite("first", Vec3<float>(10.0f, 0.0f, 0.0f), Vec3<float>(1.0f, 50.0f, 50.0f), Vec4<float>(1.0f, 1.0f, 0.0f, 1.0f));


    Vec2<float> lm_pos = window.mPos();

    while (window.Update()) {
        nbFrames++;
        renderer.render();

        if (window.currentTime - lastTime >= 1.0) {
            // Calculate frames per second and reset timer
            double fps = double(nbFrames) / (window.currentTime - lastTime);
            printf("%f fps\n", fps);

            nbFrames = 0;
            lastTime += 1.0;
        }
        //camera_look.y = ground3->rotation_euler.y;


        cat->setRotation(Vec3<float>(window.currentTime * 50.0f, 0, 0));
        //std::cout << cat->rotation_euler.x << std::endl;

        //wall1->setRotation(Vec3<float>(0, window.currentTime * -5.0f, 0));
        //wall2->setRotation(Vec3<float>(window.currentTime * -5.0f, 0, 0));
        //wall3->setRotation(Vec3<float>(window.currentTime * -5.0f, 0, 0));
        //wall4->setRotation(Vec3<float>(window.currentTime * -5.0f, 0, 0));

        float yawRadianside = toRadians(camera_look.y + 90.0f);
            Vec3<float> leftDirection(
                std::sin(yawRadianside) * movespeed,
                0.0f,
                std::cos(yawRadianside) * movespeed
            );

        float yawRadians = toRadians(camera_look.y);
            Vec3<float> forwardDirection(
                std::sin(yawRadians) * movespeed,
                0.0f,
                std::cos(yawRadians) * movespeed
            );
                //std::cout << t << std::endl;
            Vec2<float> m_pos = window.mPos();
            //std::cout << t << std::endl;

            /*m_pos.x = maths::clamp(m_pos.x, 0.0f, window.g_width());
            m_pos.y = maths::clamp(m_pos.y, 0.0f, window.g_height());*/

            int deltaX = m_pos.x - window.g_width() / 2.0f;
            int deltaY = m_pos.y - window.g_height() / 2.0f;

            lm_pos = m_pos;
            lm_pos = m_pos;

            camera_look.y += deltaX * -lookspeed * window.deltaTime();
            camera_look.x += deltaY * -lookspeed * window.deltaTime();


            //double key press is faster
        if (window.keyDown(GLFW_KEY_W)) {

            camera_pos += forwardDirection * window.deltaTime();

        }

        if (window.keyDown(GLFW_KEY_S)) {

            camera_pos -= forwardDirection * window.deltaTime();

        }

        if (window.keyDown(GLFW_KEY_A)) {

            camera_pos += leftDirection * window.deltaTime();

        }

        if (window.keyDown(GLFW_KEY_D)) {

            camera_pos -= leftDirection * window.deltaTime();

        }

        if (window.keyDown(GLFW_KEY_UP)) {
            camera_look.x += lookspeed * window.deltaTime();
        }

        if (window.keyDown(GLFW_KEY_DOWN)) {
            camera_look.x -= lookspeed * window.deltaTime();
        }


        if (window.keyDown(GLFW_KEY_LEFT)) {
            camera_look.y += lookspeed * window.deltaTime();
        }

        if (window.keyPressed(GLFW_KEY_RIGHT)) {
            camera_look.y -= lookspeed * window.deltaTime();
        }

        renderer.setUniformMat4("pr_matrix", perspective);


    

        mat4 sum = mat4::translation(camera_pos) * mat4::rotation(camera_look);
        renderer.setUniformMat4("vw_matrix", sum);

        window.setmPos(Vec2<float>(window.g_width() / 2.0f, window.g_height() / 2.0f));

        window.render();

    }

    return 0;
}