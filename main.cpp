//#include <GL/glew.h>

#include <iostream>
#include <glew.h>
#include <glfw3.h>
#include "Window.h"



int main() {

	Window window(600, 600, "Oolong", false);
	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

	while (window.Update()) {

		glBegin(GL_QUADS);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(-0.5f, 0.5f);
		glVertex2f(0.5f, 0.5f);
		glVertex2f(0.5f, -0.5f);

		window.render();
	}

	return 0;
}