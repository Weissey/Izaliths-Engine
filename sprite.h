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
	Vec2<float> m_size;


	std::vector<float> vertices {};

	std::vector<uint32_t> indices{};

	Sprite(Vec3<float> position, Vec2<float> size, Vec4<float> color)  : m_position(position), m_color(color), m_size(size) {

		name = "sprite";

		vertices = {
			// Front face
			//position.x, position.y, position.z, // Top left
			//position.x + size.x, position.y, position.z, // Top right
			//position.x + size.x, position.y + size.y, position.z, // Bottom right
			//position.x, position.y + size.y, position.z  // Bottom left

			-1.0f, 1.0f, 0.0f,
			 1.0f, 1.0f, 0.0f,
			 1.0f, -1.0f, 0.0f,
			-1.0f, -1.0f, 0.0f
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