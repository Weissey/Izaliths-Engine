#pragma once
#include <cstdint>
#include <glew.h>
#include "Maths.h"
#include <vector>
#include <iostream>
#include <sstream>
#include "Vertex.h"
#include "Utils.h"

static struct Sprite {

	std::string name;
	std::string filepath;

	Vec3<GLfloat> m_position;
	Vec4<GLfloat> m_color;
	Vec3<GLfloat> m_size;
	Vec3<GLfloat> rotation_euler;

	bool isChanged = true;

	std::vector<float> vertices {};
	std::vector<uint32_t> indices{};

	std::vector<float> uvs {};

	std::vector<Vertex> out_vertices{};
	std::vector<uint32_t> out_indices{};

	void setPosition(const Vec3<float>& pos) {
		this->m_position = pos;
		isChanged = true;
	}

	void setRotation(const Vec3<GLfloat>& euler) {
		if (rotation_euler != euler) {
			this->rotation_euler.x = customModulo(euler.x, 360.0f);
			this->rotation_euler.y = customModulo(euler.y, 360.0f);
			this->rotation_euler.z = customModulo(euler.z, 360.0f);
			isChanged = true;
		}
	}

	void rotate(const Vec3<GLfloat>& euler) {
		this->rotation_euler.x = customModulo(this->rotation_euler.x + euler.x, 360.0f);
		this->rotation_euler.y = customModulo(this->rotation_euler.y + euler.y, 360.0f);
		this->rotation_euler.z = customModulo(this->rotation_euler.z + euler.z, 360.0f);
		isChanged = true;
	}

	void translate(const Vec3<float>& pos) {
		m_position.x += pos.x;
		m_position.y += pos.y;
		m_position.z += pos.z;
		isChanged = true;
	}


	Sprite(Vec3<float> position, Vec3<float> size, Vec4<float> color, std::string name = "sprite", const char* filepath = "")
		: m_position(position), m_color(color), m_size(size), name(name) {

		isChanged = true;

		if (filepath == "") {

			printf("Loaded Default Vertices and Indices {Cube}\n");
			vertices = {
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



		}
		else {

			printf("Loaded model data from %s\n", filepath);


			FILE* file = fopen(filepath, "r");
			if (file == NULL) {
				printf("Impossible to open the file !\n");
			}
			else {
				while (1) {

					char lineHeader[128];
					// read the first word of the line
					int res = fscanf(file, "%s", lineHeader);

					if (strcmp(lineHeader, "v") == 0) {
						Vec3<float> vertex;
						fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
						vertices.push_back(vertex.x);
						vertices.push_back(vertex.y);
						vertices.push_back(vertex.z);

					}
					else if (strcmp(lineHeader, "vt") == 0) {
						Vec2<float> uv;
						fscanf(file, "%f %f\n", &uv.x, &uv.y);
						uvs.push_back(uv.x);
						uvs.push_back(uv.y);
					}
					else if (strcmp(lineHeader, "f") == 0) {
						std::string vertex1, vertex2, vertex3;
						unsigned int vertexIndex[4], uvIndex[4], normalIndex[4];
						int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n",
							&vertexIndex[0], &uvIndex[0], &normalIndex[0],
							&vertexIndex[1], &uvIndex[1], &normalIndex[1],
							&vertexIndex[2], &uvIndex[2], &normalIndex[2],
							&vertexIndex[3], &uvIndex[3], &normalIndex[3]);

						if (matches == 9) {
							indices.push_back(vertexIndex[0] - 1);
							indices.push_back(vertexIndex[1] - 1);
							indices.push_back(vertexIndex[2] - 1);
						}
						else if (matches == 12) {
							indices.push_back(vertexIndex[0] - 1);
							indices.push_back(vertexIndex[1] - 1);
							indices.push_back(vertexIndex[2] - 1);

							indices.push_back(vertexIndex[0] - 1);
							indices.push_back(vertexIndex[2] - 1);
							indices.push_back(vertexIndex[3] - 1);
						}

						//uvIndices.push_back(uvIndex[0]);
						//uvIndices.push_back(uvIndex[1]);
						//uvIndices.push_back(uvIndex[2]);
						//normalIndices.push_back(normalIndex[0]);
						//normalIndices.push_back(normalIndex[1]);
						//normalIndices.push_back(normalIndex[2]);
					}

					if (res == EOF) {
						break;
					}
				}
			}
		}

	};


	void rotateVertex(Vec3<float>& vertex, Vec3<float> center, Vec3<float> euler) {

		float roll = toRadians(euler.x);
		float pitch = toRadians(euler.y);
		float yaw = toRadians(euler.z);

		// Translate to the origin
		vertex.x -= center.x;
		vertex.y -= center.y;
		vertex.z -= center.z;

		// Apply rotation around X-axis (roll)
		float tempY = cos(roll) * vertex.y - sin(roll) * vertex.z;
		float tempZ = sin(roll) * vertex.y + cos(roll) * vertex.z;
		vertex.y = tempY;
		vertex.z = tempZ;

		// Apply rotation around Y-axis (pitch)
		float tempX = cos(pitch) * vertex.x + sin(pitch) * vertex.z;
		tempZ = -sin(pitch) * vertex.x + cos(pitch) * vertex.z;
		vertex.x = tempX;
		vertex.z = tempZ;

		// Apply rotation around Z-axis (yaw)
		tempX = cos(yaw) * vertex.x - sin(yaw) * vertex.y;
		tempY = sin(yaw) * vertex.x + cos(yaw) * vertex.y;
		vertex.x = tempX;
		vertex.y = tempY;

		// Translate back to the original position
		vertex.x += center.x;
		vertex.y += center.y;
		vertex.z += center.z;

	}








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