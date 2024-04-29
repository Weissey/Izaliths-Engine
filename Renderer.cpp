
#include "Renderer.h"
#include <vector>
#include <iostream>

#include "FenceObject.h"



Renderer::Renderer() {


    vertices = new Vertex[MaxVertexCount];
    indices = new uint32_t[MaxIndexCount];

    m_Shader = Shader::createShader("basic.vert", "basic.frag");

    glCreateVertexArrays(1, &vao);
    glBindVertexArray(vao);

    circleBuffer = new circularBuffer<Buffer>(numBuffers);

    for (size_t i = 0; i < numBuffers; i++)
    {
        initBuffer();

    }
}

void Renderer::initBuffer() {
    Buffer buffer;

    glGenBuffers(1, &buffer.VBO);
    glBindBuffer(GL_ARRAY_BUFFER, buffer.VBO);

    glCreateBuffers(1, &buffer.IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer.IBO);


    glBufferStorage(GL_ARRAY_BUFFER, MaxVertexCount * sizeof(Vertex), nullptr, flags);
    glBufferStorage(GL_ELEMENT_ARRAY_BUFFER, MaxIndexCount * sizeof(uint32_t), nullptr, flags);


    buffer.vertData = (GLfloat*)glMapBufferRange(GL_ARRAY_BUFFER, 0, MaxVertexCount * sizeof(Vertex), flags);
    glFlushMappedBufferRange(GL_ARRAY_BUFFER, 0, MaxVertexCount * sizeof(Vertex));

    buffer.indexData = (GLfloat*)glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, 0, MaxIndexCount * sizeof(uint32_t), flags);
    glFlushMappedBufferRange(GL_ELEMENT_ARRAY_BUFFER, 0, MaxIndexCount * sizeof(uint32_t));

    buffer.inUse = true;

    circleBuffer->write(buffer);
}

void Renderer::unmapBuffer(int bufferIndex) {
    glBindBuffer(GL_ARRAY_BUFFER, circleBuffer->write_ptr(bufferIndex)->VBO);
    glUnmapBuffer(GL_ARRAY_BUFFER);
    //circleBuffer->write().inUse = false;
}


void Renderer::updateBuffer(int bufferIndex) {
    std::memcpy(circleBuffer->write_ptr(bufferIndex)->vertData, vertices, MaxVertexCount * sizeof(Vertex));

    std::memcpy(circleBuffer->write_ptr(bufferIndex)->indexData, indices, MaxIndexCount * sizeof(uint32_t));
}

void Renderer::render() {
    vertexCount = 0;
    indexCount = 0;

    for (size_t i = 0; i < sprites.size(); i++)
    {
        for (size_t x = 0; x < sprites[i]->vertices.size(); x += 3) {

            Vec3<float> vert(
                sprites[i]->vertices[i + 0],
                sprites[i]->vertices[i + 1],
                sprites[i]->vertices[i + 2]
            );

            vertices[vertexCount].position.set(vert.x, vert.y, vert.z);
            vertices[vertexCount].color.set(sprites[i]->m_color.x, sprites[i]->m_color.y, sprites[i]->m_color.z, sprites[i]->m_color.c);

            vertexCount += 1;
        }


        int offset = vertexCount;

        for (size_t y = 0; y < sprites[i]->indices.size(); y += 3) {

            indices[indexCount] = (offset + sprites[i]->indices[y]);
            indices[indexCount + 1] = (offset + sprites[i]->indices[y + 1]);
            indices[indexCount + 2] = (offset + sprites[i]->indices[y + 2]);
            indexCount += 3;
        }

    }




    glBindBuffer(GL_ARRAY_BUFFER, circleBuffer->write_ptr(TbufferIndex)->VBO);

    glEnableVertexArrayAttrib(circleBuffer->write_ptr(TbufferIndex)->VBO, 0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, position));

    glEnableVertexArrayAttrib(circleBuffer->write_ptr(TbufferIndex)->VBO, 1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, color));

    glEnableVertexArrayAttrib(circleBuffer->write_ptr(TbufferIndex)->VBO, 2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, normal));

    updateBuffer(TbufferIndex);
    TbufferIndex = TbufferIndex + 1 % 3;

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glUseProgram(m_Shader->GetRendererID());
    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, circleBuffer->write_ptr(TbufferIndex)->IBO);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);

}

Renderer::~Renderer() {
    delete vertices;
    delete indices;
}

Sprite* Renderer::LoadOBJ(std::string name, Vec3<float> position, Vec3<float> size, const char* filepath) {
    Sprite* sprite = new Sprite(position, size, Vec4<float>(0.0f, 0.0f, 0.0f, 0.0f), name, filepath);
    sprites.push_back(sprite);
    return sprite;
}

void Renderer::setProjectionMatrix(const mat4& matrix) {
    glUniformMatrix4fv(glGetUniformLocation(m_Shader->GetRendererID(), "pr_matrix"), 1, GL_FALSE, matrix.elements);
}