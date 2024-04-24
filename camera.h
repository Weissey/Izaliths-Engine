#pragma once
#include "Maths.h"
#include "Window.h"
#include <glew.h>
#include <glfw3.h>

struct Camera {

	Vec3<float> pos;
	Vec3<float> euler;

	Camera(const Vec3<float>& pos, const Vec3<float>& euler);

	void Translate(const Vec3<float>& pos);

	void Rotate(const Vec3<float>& euler);

	void SetPosition(const Vec3<float>& pos);

	void SetRotate(const Vec3<float>& euler);

	mat4 render();
};

class FPScam {

public:
	FPScam(Vec3<float> pos, Vec3<float> euler, Window& m_window);
    Window* c_window;

    Vec2<float> curr_mouse_pos;

	Vec3<float> camera_pos;
	Vec3<float> camera_look;

	float movespeed = 400.0f;
	float lookspeed = 60.0f;

    mat4 render();

	void setControls(int w, int s, int a, int d);

    int foward_keycode = GLFW_KEY_W, back_keycode = GLFW_KEY_S, left_keycode = GLFW_KEY_A, right_keycode = GLFW_KEY_D;

};