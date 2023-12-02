#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Renderer.h"
#include <iostream>



Renderer::Renderer() { }

void Renderer::start() {

    const size_t MaxQuadCount = 10000;
    const size_t MaxVertexCount = MaxQuadCount * 4;
    const size_t MaxIndexCount = MaxQuadCount * 6;

    vertices = std::array<Vertex, 10000>();
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

    uint32_t indices[MaxIndexCount];
    uint32_t offset = 0;

    for (size_t i = 0; i < MaxIndexCount; i += 6)
    {
        indices[i + 0] = 0 + offset;
        indices[i + 1] = 1 + offset;
        indices[i + 2] = 2 + offset;

        indices[i + 3] = 2 + offset;
        indices[i + 4] = 3 + offset;
        indices[i + 5] = 0 + offset;

        offset += 4;
    }

    glCreateBuffers(1, &m_SpriteIB);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_SpriteIB);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

}

Sprite* Renderer::CreateSprite(Vec3<float> position, Vec2<float> size, Vec4<float> color) {
    Sprite* p_sprite = new Sprite(position, size, color);
    spriteList.push_back(p_sprite);
    return p_sprite;
}


void Renderer::render() {
    indexCount = 0;
    //ImguiCode();
    buffer = vertices.data();


    for (auto i = 0; i < spriteList.size(); i++)
    {
        addBuffers(spriteList[i]);
    }

    //spriteList[0].m_position.set(x, 0.0f, 0.0f);

    glBindBuffer(GL_ARRAY_BUFFER, m_SpriteVB);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

    glUseProgram(m_Shader->GetRendererID());
    glBindVertexArray(m_SpriteVA);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);

}

void Renderer::CreateSquare(float x, float y) {
    float size = 0.5f;

    buffer->position.set(x, y, 0.0f);
    buffer->color.set(1.0f, 1.0f, 0.0f, 1.0f);
    buffer++;

    buffer->position.set(x + size, y, 0.0f);
    buffer->color.set(1.0f, 1.0f, 0.0f, 1.0f);
    buffer++;

    buffer->position.set(x + size, y + size, 0.0f);
    buffer->color.set(1.0f, 1.0f, 1.0f, 1.0f);
    buffer++;

    buffer->position.set(x, y + size, 0.0f);
    buffer->color.set(1.0f, 1.0f, 1.0f, 1.0f);
    buffer++;

    indexCount += 6;
}


void Renderer::addBuffers(const Sprite* sprite) {

    for (size_t i = 0; i < sprite->vertices.size(); i += 3) {

        buffer->position.set(
            sprite->vertices[i] * (sprite->m_size.x / 2) + sprite->m_position.x,
            sprite->vertices[i + 1] * (sprite->m_size.y / 2) + sprite->m_position.y,
            sprite->vertices[i + 2] + sprite->m_position.z);

        buffer->color.set(sprite->m_color.x, sprite->m_color.y, sprite->m_color.z, sprite->m_color.c);
        buffer++;
    }
    indexCount += 6;
}

void Renderer::setUniformMat4(const GLchar* name, const mat4& matrix)
{
    glUniformMatrix4fv(glGetUniformLocation(m_Shader->GetRendererID(), name), 1, GL_FALSE, matrix.elements);
}

void Renderer::ImguiCode() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Test");
    ImGui::DragFloat("x", &spriteList[1]->m_position.x, 1.0f, -1200.0f, 1200.0f);
    ImGui::DragFloat("y", &spriteList[1]->m_position.y, 1.0f, -1200.0f, 1200.0f);
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}