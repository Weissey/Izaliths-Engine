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

	float g_width();
	float g_height();

	float deltaTime();

	float currentTime = 0.0f;
	float lastTime = glfwGetTime();
	float lastoTime = glfwGetTime();

	GLsync fenceSync;

	float f_deltaTime;

	int nbFrames = 0;

	Vec2<float> mPos();
	void setmPos(Vec2<float> pos);


	bool keyUp(int keycode);
	bool keyDown(int keycode);
	bool keyPressed(int keycode);

	void setBackgroundColor(float red, float green, float blue, float alpha);
private:
	int width;
	int height;
	const char* title;
	bool fullscreen_mode;

	Vec4<float> bg_color;

	GLFWwindow* window;

	bool m_Keys[MAX_KEYS];
	bool m_MouseButtons[MAX_BUTTONS];
};