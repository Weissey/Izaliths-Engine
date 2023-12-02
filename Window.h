#pragma once
#include <glew.h>
#include <glfw3.h>
#include "Maths.h"

#define MAX_KEYS	1024
#define MAX_BUTTONS	32

class Window {

public:
	Window(int w_width, int w_height, const char* w_title, bool w_fullscreen_mode);
	bool Update();
	void render();

	int g_width();
	int g_height();

	Vec2<float> mPos();


	bool key(int key);
private:
	int width;
	int height;
	const char* title;
	bool fullscreen_mode;
	GLFWwindow* window;

	bool m_Keys[MAX_KEYS];
	bool m_MouseButtons[MAX_BUTTONS];
	double mx, my;
};