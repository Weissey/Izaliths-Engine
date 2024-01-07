#pragma once
#include "Maths.h"
#include "Window.h"
#include <glew.h>
#include <glfw3.h>

struct Camera {

	Vec3<float> pos;
	Vec3<float> euler;

	Camera(Vec3<float> pos, Vec3<float> euler);

	void Translate(Vec3<float> pos);

	void Rotate(Vec3<float> euler);

	void SetPosition(Vec3<float> pos);

	void SetRotate(Vec3<float> euler);

	mat4 render();
};

class FPScam {

public:
	FPScam(Vec3<float> pos, Vec3<float> euler, Window& m_window);
    Window* c_window;

    Vec2<float> curr_mouse_pos;

	Vec3<float> camera_pos;
	Vec3<float> camera_look;

	float movespeed = 20.0f;
	float lookspeed = 40.0f;

    mat4 render();

	void setControls(int w, int s, int a, int d);

    int foward_keycode = GLFW_KEY_W, back_keycode = GLFW_KEY_S, left_keycode = GLFW_KEY_A, right_keycode = GLFW_KEY_D;

};