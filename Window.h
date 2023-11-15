#pragma once
#include <glew.h>
#include <glfw3.h>

class Window {

public:
	Window(int w_width, int w_height, const char* w_title, bool w_fullscreen_mode);
	bool Update();
	void render();

private:
	int width;
	int height;
	const char* title;
	bool fullscreen_mode;
	GLFWwindow* window;
};