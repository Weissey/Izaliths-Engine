#pragma once
#include <cstdint>
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


static struct Sprite {

	std::string name;
	std::string filepath;

	Vec3<float> m_position;
	Vec4<float> m_color;
	Vec3<float> m_size;
	Vec3<float> rotation_euler;


	std::vector<float> vertices {};

	std::vector<uint32_t> indices{};

	void setRotation(Vec3<float> euler) {
		rotation_euler = euler;
	}

	void rotate(Vec3<float> euler) {
		rotation_euler.x += euler.x;
		rotation_euler.y += euler.y;
		rotation_euler.z += euler.z;
	}

	Sprite(Vec3<float> position, Vec3<float> size, Vec4<float> color, std::string name = "sprite", const char* filepath = "")
		: m_position(position), m_color(color), m_size(size), name(name) {

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