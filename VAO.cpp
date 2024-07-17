#include "VAO.hpp"
#include<iostream>
namespace Graphics
{
    VAO::VAO()
    {
    }
    void VAO::Init()
    {
        glGenVertexArrays(1, &ID);
    }
    void VAO::LinkVBO(VBO& VBO, GLuint layout, GLuint divisor)
    {
        glEnableVertexAttribArray(layout);
        VBO.Bind();
        glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        VBO.UnBind();
        glVertexAttribDivisor(layout, divisor);
    }
    void VAO::Bind()
    {
        glBindVertexArray(ID);
    }
    void VAO::UnBind()
    {
        glBindVertexArray(0);
    }
    void VAO::Delete()
    {
        glDeleteVertexArrays(1, &ID);
    }
    GLuint VAO::GetID()
    {
        return ID;
    }
}