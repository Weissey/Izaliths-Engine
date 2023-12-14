#pragma once
#include <cstdint>
#include "Maths.h"
#include <vector>
#include <iostream>

struct Vertex {
	Vec3<float> position;
	Vec4<float> color;
};


static struct Sprite {

	std::string name;
	Vec3<float> m_position;
	Vec4<float> m_color;
	Vec3<float> m_size;
	Vec3<float> rotation_euler;


	std::vector<float> vertices {};

	std::vector<uint32_t> indices{};

	void rotate(Vec3<float> euler) {
		rotation_euler = euler;
	}

	Sprite(Vec3<float> position, Vec3<float> size, Vec4<float> color, std::string name = "sprite") : m_position(position), m_color(color), m_size(size), name(name) {

		vertices = {
			// Front face
			//position.x, position.y, position.z, // Top left
			//position.x + size.x, position.y, position.z, // Top right
			//position.x + size.x, position.y + size.y, position.z, // Bottom right
			//position.x, position.y + size.y, position.z  // Bottom left

			-1.0f, 1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f, 1.0f, 1.0f,
			-1.0f, -1.0f, 1.0f,

			1.0f, 1.0f, -1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, -1.0f, 1.0f,
			1.0f, -1.0f, -1.0f

		};

		indices = {
			0, 1, 3, 2, 3, 0,

			4, 0, 2, 4, 5, 2,

			2, 3, 6, 2, 6, 5,

			1, 3, 7, 3, 6, 7,

			4, 6, 5, 4, 7, 6,

			0, 4, 7, 0, 1, 7
		};

	
	};















	bool onClick(float mx, float my) {
		
		if (mx >= m_position.x - m_size.x / 2 && mx <= m_position.x + m_size.x / 2) {
			if (my >= m_position.y - m_size.y / 2 && my <= m_position.y + m_size.y / 2) {
				return true;
			}
		}
		return false;
	};

	Vec4<float> getBounds() const {
		return Vec4<float>(m_position.x - m_size.x / 2, m_position.x + m_size.x / 2, m_position.y - m_size.y / 2, m_position.y + m_size.y / 2);
	}

	bool isBoxTouching(const Sprite& sprite) {
		
		Vec4<float> m = this->getBounds();
		Vec4<float> s = sprite.getBounds();

		if (	m.x <= s.y	&&
				m.y >= s.x	&&
				m.z <= s.c	&&
				m.c >= s.z	) {
			return true;
		}

		return false;
	}

};