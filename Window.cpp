
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

}

bool Window::Update() {

    if (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        return true;
    }

    glfwDestroyWindow(window);
    return false;
}

void Window::render() {
    glfwPollEvents();
    glfwSwapBuffers(window);
}