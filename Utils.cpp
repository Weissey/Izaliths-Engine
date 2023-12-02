#include "Utils.h"
#include <fstream>
#include <iostream>

std::string file_to_char(const std::string& filepath) {

	std::string result;
	std::ifstream in(filepath, std::ios::in | std::ios::binary);
	if (in)
	{
		in.seekg(0, std::ios::end);
		result.resize((size_t)in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&result[0], result.size());
		in.close();
	}
	else {
		return NULL;
	}

	std::cout << result << std::endl;

	return result;
	
}

#define _USE_MATH_DEFINES
#include <math.h>
float toRadians(float degrees)
{
	return degrees * (M_PI / 180.0f);
}