#pragma once
#include "C:/msys64/mingw64/lib/glad/include/glad/glad.h"

namespace Graphics
{
    class VBO
    {
        private:
        GLuint ID;
        public:
        VBO(GLfloat* vertices, GLsizeiptr size);
        void Bind();
        void UnBind();
        void Delete();
        GLuint GetID();
    };
}