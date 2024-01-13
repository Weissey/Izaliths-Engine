#pragma once

#include "Maths.h"
#include <array>
#include "sprite.h"

class Rigidbody2D {
public:
	void cubeCollider(Sprite sprite, Vec3<float> bounds, bool show_bounds = false);

	bool touching = false;

	struct edges {
		Vec2<float> edge_axis;
		Vec4<float> edge_color;
	};

	std::array<edges, 4> edgeList; //+6 for render

};