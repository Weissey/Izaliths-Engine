#include "camera.h"



Camera::Camera(Vec3<float> pos, Vec3<float> euler)
{
	this->pos = pos;
	this->euler = euler;
}

void Camera::Translate(Vec3<float> pos)
{
	this->pos += pos;
}

void Camera::Rotate(Vec3<float> euler)
{
	this->euler += euler;
}

void Camera::SetPosition(Vec3<float> pos)
{
	this->pos = pos;
}

void Camera::SetRotate(Vec3<float> euler)
{
	this->euler = euler;
}

mat4 Camera::render()
{
    return mat4::translation(pos) * mat4::rotation(euler);
}

FPScam::FPScam(Vec3<float> pos, Vec3<float> euler, Window& m_window) {
    camera_pos = pos;
    camera_look = euler;

    c_window = &m_window;


}

mat4 FPScam::render()
{

    float yawRadiansFoward = toRadians(camera_look.y);
    Vec3<float> forwardDirection(std::sin(yawRadiansFoward) * movespeed, 0.0f, std::cos(yawRadiansFoward)* movespeed);

    float yawRadiansLeft = toRadians(camera_look.y + 90.0f);
    Vec3<float> leftDirection(std::sin(yawRadiansLeft) * movespeed, 0.0f, std::cos(yawRadiansLeft) * movespeed);


    curr_mouse_pos = c_window->mPos();

    c_window->setmPos(Vec2<float>(c_window->g_width() / 2.0f, c_window->g_height() / 2.0f));

    int deltaX = curr_mouse_pos.x - c_window->g_width() / 2.0f;
    int deltaY = curr_mouse_pos.y - c_window->g_height() / 2.0f;


    camera_look.y -= deltaX * lookspeed * c_window->deltaTime();
    camera_look.x -= deltaY * lookspeed * c_window->deltaTime();

    if (c_window->keyDown(foward_keycode)) {
        camera_pos += forwardDirection * c_window->deltaTime();
    }

    if (c_window->keyDown(back_keycode)) {
        camera_pos -= forwardDirection * c_window->deltaTime();
    }

    if (c_window->keyDown(left_keycode)) {
        camera_pos += leftDirection * c_window->deltaTime();
    }

    if (c_window->keyDown(right_keycode)) {
        camera_pos -= leftDirection * c_window->deltaTime();
    }

    mat4 sum = mat4::translation(camera_pos) * mat4::rotation(camera_look);


    return sum;

}

void FPScam::setControls(int w, int s, int a, int d)
{
    foward_keycode = w;
    back_keycode = s;
    left_keycode = a;
    right_keycode = d;
}
