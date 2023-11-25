#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Renderer.h"
#include <iostream>


Renderer::Renderer() { }

void Renderer::start() {

    const size_t MaxQuadCount = 1000;
    const size_t MaxVertexCount = MaxQuadCount * 4;
    const size_t MaxIndexCount = MaxQuadCount * 6;

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


void Renderer::render() {
    indexCount = 0;
    ImguiCode();
    buffer = vertices.data();
    CreateSquare(0, 0); //here

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

void Renderer::ImguiCode() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Test");
    /*ImGui::DragFloat("po1", &pos.x, 0.01f, -5.0f, 5.5f);
    ImGui::DragFloat("po", &pos.y, 0.01f, -5.0f, 5.5f);*/
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}