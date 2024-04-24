
#include "Renderer.h"
#include <vector>
#include <iostream>

#include "FenceObject.h"



Renderer::Renderer() {

    m_SpriteIB = 0;
    m_SpriteVA = 0;
    m_SpriteVB = 0;

    vertices = new Vertex[MaxVertexCount];
    indices = new uint32_t[MaxIndexCount];

    m_Shader = Shader::createShader("basic.vert", "basic.frag");

    glCreateVertexArrays(1, &m_SpriteVA);
    glBindVertexArray(m_SpriteVA);

    glCreateBuffers(1, &m_SpriteVB);
    glBindBuffer(GL_ARRAY_BUFFER, m_SpriteVB);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * MaxVertexCount, nullptr, GL_DYNAMIC_DRAW);

    glEnableVertexArrayAttrib(m_SpriteVB, 0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, position));

    glEnableVertexArrayAttrib(m_SpriteVB, 1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, color));

    glEnableVertexArrayAttrib(m_SpriteVB, 2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, normal));

    glCreateBuffers(1, &m_SpriteIB);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_SpriteIB);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * MaxIndexCount, nullptr, GL_DYNAMIC_DRAW);
}

Renderer::~Renderer() {
    delete vertices;
    delete indices;
}

Sprite* Renderer::CreateSprite(std::string name, Vec3<float> position, Vec3<float> size, Vec4<float> color) {
    Sprite* sprite = new Sprite(position, size, color, name);
    spriteList.push_back(sprite);
    return sprite;
}

Sprite* Renderer::LoadOBJ(std::string name, Vec3<float> position, Vec3<float> size, const char* filepath, Vec4<float> color) {
    Sprite* sprite = new Sprite(position, size, color, name, filepath);
    spriteList.push_back(sprite);
    return sprite;
}

void Renderer::setActiveCamera(Camera& camera) {
    glUniformMatrix4fv(glGetUniformLocation(m_Shader->GetRendererID(), "vw_matrix"), 1, GL_FALSE, camera.render().elements);
}

void Renderer::setActiveCamera(FPScam& camera) {
    glUniformMatrix4fv(glGetUniformLocation(m_Shader->GetRendererID(), "vw_matrix"), 1, GL_FALSE, camera.render().elements);
}

void Renderer::setProjectionMatrix(const mat4& matrix) {
    glUniformMatrix4fv(glGetUniformLocation(m_Shader->GetRendererID(), "pr_matrix"), 1, GL_FALSE, matrix.elements);
}



void Renderer::render() {


    num = 0;

    last_num = 0;



    //ImguiCode();

    for (size_t i = 0; i < spriteList.size() - 1; ++i) {
        for (size_t j = 0; j < spriteList.size() - i - 1; ++j) {
            if (spriteList[j]->isChanged > spriteList[j + 1]->isChanged) {
                // Swap the pointers if necessary
                swapPointers(spriteList[j], spriteList[j + 1]);
                num++;
            }
        }
    }

    vertexCount = 0;
    indexCount = 0;

    int updateVertexCount = 0;
    int updateIndiceCount = 0;

    startVertexIndex = 0;
    startIndiceIndex = 0;


    for (size_t i = 0; i < spriteList.size(); i++)
    {
        //std::cout << i;
        if (spriteList[i]->isChanged == true || num != 0) {

            compileIndices(spriteList[i]); //if static do once
            compileVertices(spriteList[i]);

            spriteList[i]->isChanged = false;

            updateVertexCount += spriteList[i]->vertices.size();
            updateIndiceCount += spriteList[i]->indices.size();

        }
        else {
            indexCount += spriteList[i]->indices.size();
            vertexCount += spriteList[i]->vertices.size();

            startVertexIndex += spriteList[i]->vertices.size();
            startIndiceIndex += spriteList[i]->indices.size();
        }

    }

    if (num != last_num) {
        startVertexIndex = 0;
        startIndiceIndex = 0;

        updateVertexCount = vertexCount;
        updateIndiceCount = indexCount;

    }

    last_num = num;

    if (updateVertexCount != 0) {
        glBindBuffer(GL_ARRAY_BUFFER, m_SpriteVB);
        glBufferSubData(GL_ARRAY_BUFFER, startVertexIndex * sizeof(Vertex), updateVertexCount * sizeof(Vertex), &vertices[startVertexIndex]);
    }

    if (updateIndiceCount != 0) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_SpriteIB);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, startIndiceIndex * sizeof(uint32_t), updateIndiceCount * sizeof(uint32_t), &indices[startIndiceIndex]);
    }


    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glUseProgram(m_Shader->GetRendererID());
    glBindVertexArray(m_SpriteVA);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
}

void Renderer::compileVertices(Sprite* sprite)
{

    for (size_t i = 0; i < sprite->vertices.size(); i += 3) {

        Vec3<float> vert(
            sprite->vertices[i + 0] * (sprite->m_size.x * halfSizeFactor) + sprite->m_position.x,
            sprite->vertices[i + 1] * (sprite->m_size.y * halfSizeFactor) + sprite->m_position.y,
            sprite->vertices[i + 2] * (sprite->m_size.z * halfSizeFactor) + sprite->m_position.z
        );

        rotateVertex(vert, sprite->m_position, sprite->rotation_euler);

        vertices[vertexCount].position.set(vert.x, vert.y, vert.z);
        vertices[vertexCount].color.set(sprite->m_color.x, sprite->m_color.y, sprite->m_color.z, sprite->m_color.c);

        vertexCount += 1;

    }
}

void Renderer::compileIndices(Sprite* sprite) {

    int offset = vertexCount;
        
    for (size_t i = 0; i < sprite->indices.size(); i += 3) {

        indices[indexCount] = (offset + sprite->indices[i]);
        indices[indexCount + 1] = (offset + sprite->indices[i + 1]);
        indices[indexCount + 2] = (offset + sprite->indices[i + 2]);
        indexCount += 3;
    }
}

void Renderer::setUniformMat4(const GLchar* name, const mat4& matrix)
{
    glUniformMatrix4fv(glGetUniformLocation(m_Shader->GetRendererID(), name), 1, GL_FALSE, matrix.elements);
}

void Renderer::setVec4(const GLchar* name, const Vec4<float>& color)
{
    glUniform4f(glGetUniformLocation(m_Shader->GetRendererID(), name), color.x, color.y, color.z, color.c);
}

void Renderer::setVec3(const GLchar* name, const Vec3<float>& color)
{
    glUniform3f(glGetUniformLocation(m_Shader->GetRendererID(), name), color.x, color.y, color.z);
}

void Renderer::rotateVertex(Vec3<float> &vertex, const Vec3<float> &center, const Vec3<float> &euler) {

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