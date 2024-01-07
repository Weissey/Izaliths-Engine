#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Renderer.h"
#include <iostream>



Renderer::Renderer() {

    vertices.resize(MaxQuadCount);

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

Sprite* Renderer::CreateSprite(std::string name, Vec3<float> position, Vec3<float> size, Vec4<float> color) {
    Sprite* sprite = new Sprite(position, size, color, name);
    spriteList.push_back(sprite);
    return sprite;
}

Sprite* Renderer::LoadOBJ(std::string name, Vec3<float> position, Vec3<float> size, const char* filepath) {
    Sprite* sprite = new Sprite(position, size, Vec4<float>(0.1f, 1.0f, 0.1f, 1.0f), name, filepath);
    spriteList.push_back(sprite);
    return sprite;
}

void Renderer::setActiveCamera(Camera& camera) {
    glUniformMatrix4fv(glGetUniformLocation(m_Shader->GetRendererID(), "vw_matrix"), 1, GL_FALSE, camera.render().elements);
}

void Renderer::setActiveCamera(FPScam& camera) {
    glUniformMatrix4fv(glGetUniformLocation(m_Shader->GetRendererID(), "vw_matrix"), 1, GL_FALSE, camera.render().elements);
}


void Renderer::render() {

    vertexCount = 0;
    indexCount = 0;

    buffer = vertices.data();

    //ImguiCode();

    vertices.clear();
    vertices.resize(MaxQuadCount);


    for (size_t i = 0; i < spriteList.size(); i++)
    {
        addBuffers(spriteList[i]);
    }

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glBindBuffer(GL_ARRAY_BUFFER, m_SpriteVB);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_SpriteIB);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(indices), indices);

    glUseProgram(m_Shader->GetRendererID());
    glBindVertexArray(m_SpriteVA);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Renderer::addBuffers(const Sprite* sprite) {

    int offset = vertexCount;

    float color_p = 0.0f;

    for (size_t i = 0; i < sprite->vertices.size(); i += 3) {

       Vec3<float> vert(sprite->vertices[i] * (sprite->m_size.x / 2) + sprite->m_position.x,
            sprite->vertices[i + 1] * (sprite->m_size.y / 2) + sprite->m_position.y,
            sprite->vertices[i + 2] * (sprite->m_size.z / 2) + sprite->m_position.z);
        
        rotateVertex(vert, sprite->m_position, sprite->rotation_euler);

        vertices.at(vertexCount).position.set(vert.x, vert.y, vert.z);
        vertices.at(vertexCount).color.set(sprite->m_color.x, sprite->m_color.y, sprite->m_color.z, sprite->m_color.c);

        vertexCount += 1;
    }

    for (size_t i = 0; i < sprite->indices.size(); i += 3)
    {
        indices[indexCount] = offset + sprite->indices[i];
        indices[indexCount + 1] = offset + sprite->indices[i + 1];
        indices[indexCount + 2] = offset + sprite->indices[i + 2];
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

void Renderer::ImguiCode() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Test");
    ImGui::DragFloat("x pos", &spriteList[2]->rotation_euler.x, 1.0f, -1200.0f, 1200.0f);
    ImGui::DragFloat("z pos", &spriteList[2]->rotation_euler.z, 0.1f, -1200.0f, 1200.0f);
    ImGui::DragFloat("yaw", &spriteList[2]->rotation_euler.y, 0.1f, -360.0f, 360.0f);


    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Renderer::TranslateCamera(Vec3<float> pos)
{
    setUniformMat4("vw_matrix", mat4::translation(pos));
}

void Renderer::RotateCamera(Vec3<float> angles)
{
    setUniformMat4("vw_matrix", mat4::rotation(angles));
}

void Renderer::rotateVertex(Vec3<float> &vertex, Vec3<float> center, Vec3<float> euler) {

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