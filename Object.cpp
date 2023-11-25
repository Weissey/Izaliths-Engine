

#include "Object.h"


Object::Object() {
	
}

Object::~Object() {
	
}

GLfloat* Object::GetList() {
    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f,   // Vertex 1
         0.5f, -0.5f, 0.0f,   // Vertex 2
         0.0f,  0.5f, 0.0f    // Vertex 3
    };
    return vertices;
}