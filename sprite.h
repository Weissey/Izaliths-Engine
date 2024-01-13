#pragma once
#include <cstdint>
#include <glew.h>
#include "Maths.h"
#include <vector>
#include <iostream>
#include <sstream>
#include "Utils.h"

struct Vertex {

	Vec3<float> position;
	Vec4<float> color;
	Vec3<float> normal;
};

struct Transform {
	Transform(float x, float y, float z, float a, float b, float c) {
		this->position.set(x, y, z);
		this->rotation.set(a, b, c);
	}
	Vec3<float> position;
	Vec3<float> rotation;
};


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

	std::vector<Vertex> out_vertices{};
	std::vector<uint32_t> out_indices{};

	std::vector<Transform> transformations{};

	void setPosition(const Vec3<float>& pos) {
		this->m_position = pos;
		transformations.push_back(Transform(1, 2, 3, 4, 5, 6));
	}

	void setRotation(const Vec3<float>& euler) {
		this->rotation_euler = euler;
		isChanged = true;
	}

	void rotate(const Vec3<float>& euler) {
		rotation_euler.x += euler.x;
		rotation_euler.y += euler.y;
		rotation_euler.z += euler.z;
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

			//printf("Loaded model data from %s\n", filepath);


			FILE* file;
			if (fopen_s(&file, filepath, "r") == 0) {


				char buffer[1024];


				while (fgets(buffer, sizeof(buffer), file) != nullptr) {
					std::istringstream iss(buffer);

					std::string token;
					iss >> token;

					// Check if the first token is "v"
					if (token == "v") {
						// Read the float values into variables
						float x, y, z;
						iss >> x >> y >> z;

						// Check if extraction was successful
						if (!iss.fail()) {
							// Print the extracted values
							//std::cout << "vert: " << x << " " << y << " " << z << "\n";
							vertices.push_back(x);
							vertices.push_back(y);
							vertices.push_back(z);
						}
						else {
							std::cerr << "Extraction failed.\n";
						}
					}

					if (token == "f") {
						// Read the float values into variables

						char slash;

						float face[3];

						for (int n = 0; n < 3; n++)
						{
							float indice, y, z;

							iss >> indice;

							face[n] = indice;

							//std::cout << "face: " << indice << " " << y << " " << z << "\n";

							if (!iss.fail()) {
								// Print the extracted values

							}
							else {
								std::cerr << "Extraction failed.\n";
							}
						}
						indices.push_back(face[0] - 1);
						indices.push_back(face[1] - 1);
						indices.push_back(face[2] - 1);
					}
				}

				fclose(file);
				std::cerr << "Model Loaded\n";
			}
			else {
				printf("File cannot be opened\n");
				// Handle the error

				if (0 == "f") {
					// Read the float values into variables


					float face[3];

					for (int n = 0; n < 3; n++)
					{
						float indice, y, z;
						char slash;

						//iss >> indice >> slash >> y >> slash >> z;

						//face[n] = indice;

						//std::cout << n << " - face: " << indice << " " << y << " " << z << "\n";

						//if (!iss.fail()) {
						//	// Print the extracted values

						//}
						//else {
						//	std::cerr << "Extraction failed.\n";
						//}
					}

					indices.push_back(face[0]);
					indices.push_back(face[1]);
					indices.push_back(face[2]);

					/*indices.push_back(face[0]);
					indices.push_back(face[2]);
					indices.push_back(face[3]);*/
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