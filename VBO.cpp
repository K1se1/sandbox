#include "VBO.hpp"

namespace Graphics
{
    VBO::VBO(GLfloat* vertices, GLsizeiptr size)
    {
        glGenBuffers(1, &ID);
        glBindBuffer(GL_ARRAY_BUFFER, ID);
        glBufferData(GL_ARRAY_BUFFER, size, &vertices[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

    }
    VBO::VBO(GLfloat** vertices, GLsizeiptr size)
    {
        glGenBuffers(1, &ID);
        glBindBuffer(GL_ARRAY_BUFFER, ID);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

    }

    void VBO::Bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, ID);
    }

    void VBO::UnBind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void VBO::Delete()
    {
        glDeleteBuffers(1, &ID);
    }

    GLuint VBO::GetID()
    {
        return ID;
    }

}