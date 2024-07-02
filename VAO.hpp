#pragma once
#include "VBO.hpp"
#include "C:/msys64/mingw64/lib/glad/include/glad/glad.h"

namespace Graphics
{
    class VAO
    {
        private:
        GLuint ID;
        public:
        VAO();
        void LinkVBO(VBO& VBO, GLuint layout);
        void Bind();
        void UnBind();
        void Delete();
        GLuint GetID();
    };
}