#pragma once
#include "../glad/glad.h"

namespace Graphics
{
    // Класс для буффера вершин
    class VBO
    {
        private:
        GLuint ID;
        public:
        VBO(GLfloat* vertices, GLsizeiptr size);
        VBO(GLfloat** vertices, GLsizeiptr size);
        void Bind();
        void UnBind();
        void Delete();
        GLuint GetID();
    };
}