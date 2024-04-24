
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Window.h"
#include <iostream>

Window::Window(int w_width, int w_height, const char* w_title, bool w_fullscreen_mode)
    : width(w_width), height(w_height), title(w_title), fullscreen_mode(w_fullscreen_mode) {


    for (size_t i = 0; i < MAX_KEYS; i++) { m_Keys[i] = false; }

    for (size_t i = 0; i < MAX_BUTTONS; i++) { m_MouseButtons[i] = false; }

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
    //glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    //glfwWindowHint(GLFW_SAMPLES, 4);



    if (w_fullscreen_mode) {
	    window = glfwCreateWindow(width, height, title, glfwGetPrimaryMonitor(), NULL);
    }
    else {
        window = glfwCreateWindow(width, height, title, NULL, NULL);
    }

    glfwMakeContextCurrent(window);

    if (!window) {
        std::cout << "Window Initialization Failed\n";
        glfwTerminate();
    }
    else {
        std::cout << "Window Initialization Successful\n";
    }


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
    //glEnable(GL_CULL_FACE);
    //glEnable(GL_MULTISAMPLE);
    //glDepthFunc(GL_LESS);

    //glDepthMask(GL_FALSE);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    bg_color.set(0.2f, 0.3f, 0.8f, 1.0f);
    glClearColor(bg_color.x, bg_color.y, bg_color.z, bg_color.c);
}

float Window::deltaTime() {

    return f_deltaTime;
}

bool Window::Update() {



    if (!glfwWindowShouldClose(window)) {
        f_deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        currentTime = glfwGetTime();

        nbFrames++;

        if (currentTime - lastoTime >= 1.0) {
            // Calculate frames per second and reset timer
            double fps = double(nbFrames) / (currentTime - lastoTime);
            printf("%f fps\n", fps);
            nbFrames = 0;
            lastoTime += 1.0;
        }

        glClientWaitSync(fenceSync, GL_SYNC_FLUSH_COMMANDS_BIT, GL_TIMEOUT_IGNORED);
        glfwPollEvents();
        glfwSwapBuffers(window);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        return true;
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);

    return false;
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

void Window::setmPos(Vec2<float> pos) {
    glfwSetCursorPos(window, pos.x, pos.y);
}

bool Window::keyDown(int keycode) {
    
    m_Keys[keycode] = glfwGetKey(window, keycode) == GLFW_PRESS;
    //std::cout << "down" << std::endl;
    return m_Keys[keycode];
}

bool Window::keyUp(int keycode) {
    m_Keys[keycode] = glfwGetKey(window, keycode) == GLFW_RELEASE;
    //std::cout << "up" << std::endl;
    return m_Keys[keycode];
}

bool Window::keyPressed(int keycode) { // fix

    if (keycode >= MAX_KEYS)
        return false;

    if (m_Keys[keycode] || glfwGetKey(window, keycode) == GLFW_PRESS) {
        m_Keys[keycode] = true;

        if (glfwGetKey(window, keycode) == GLFW_RELEASE) {
            m_Keys[keycode] = false;
            return true;
        }
    }

    return false;

}

void Window::setBackgroundColor(float red, float green, float blue, float alpha) {
    this->bg_color.set(red, green, blue, alpha);
    glClearColor(bg_color.x, bg_color.y, bg_color.z, bg_color.c);
}
