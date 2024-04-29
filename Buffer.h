#pragma once

struct Buffer {
    GLuint VBO; // Vertex Buffer Object ID
    GLuint IBO; // Vertex Buffer Object ID
    GLfloat* vertData; // Pointer to mapped data
    GLfloat* indexData;
    bool inUse; // Indicates if the buffer is currently mapped
};