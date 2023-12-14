
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Window.h"
#include <iostream>

Window::Window(int w_width, int w_height, const char* w_title, bool w_fullscreen_mode)
    : width(w_width), height(w_height), title(w_title), fullscreen_mode(w_fullscreen_mode) {

    if (!glfwInit()) {
        std::cout << "GFLW Initialization Failed\n";
        glfwTerminate();
    }
    else {
        std::cout << "GLFW Initialization Successful\n";
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



    if (w_fullscreen_mode) {
	    window = glfwCreateWindow(width, height, title, glfwGetPrimaryMonitor(), NULL);
    }
    else {
        window = glfwCreateWindow(width, height, title, NULL, NULL);
    }


    if (!window) {
        std::cout << "Window Initialization Failed\n";
        glfwTerminate();
    }
    else {
        std::cout << "Window Initialization Successful\n";
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cout << "GLEW Initialization Failed\n";
        fprintf(stderr, "Error initializing GLEW: %s\n", glewGetErrorString(glewInit()));
        glfwTerminate();

    } else {
        std::cout << "GLEW Initialization Successful\n";
    }

    // input //
    for (int i = 0; i < MAX_KEYS; i++) {
        m_Keys[i] = false;
    }

    for (int i = 0; i < MAX_BUTTONS; i++) {
        m_MouseButtons[i] = false;
    }


    glViewport(0, 0, width, height);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    //glDepthMask(GL_FALSE);*/

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

}

float Window::deltaTime() {

    return f_deltaTime;
}

bool Window::Update() {

    f_deltaTime = currentTime - lastTime;
    lastTime = currentTime;

    if (!glfwWindowShouldClose(window)) {
        currentTime = glfwGetTime();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        return true;
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);

    return false;
}

void Window::render() {
    glfwPollEvents();
    glfwSwapBuffers(window);
}

float Window::g_width() {
    return this->width;
}

float Window::g_height() {
    return this->height;
}

Vec2<float> Window::mPos() {
    Vec2<double> pos;
    glfwGetCursorPos(window, &pos.x, &pos.y);
    return Vec2<float>(pos.x, pos.y);
}

bool Window::key(int key, bool keyboard) {
    if (keyboard) {
        return glfwGetKey(window, key) == GLFW_PRESS;
    }
    return glfwGetMouseButton(window, key) == GLFW_PRESS;
}