#pragma once
#include "VBO.hpp"
#include "../glad/glad.h"

namespace Graphics
{
    // класс для массива вершин
    class VAO
    {
        private:
        GLuint ID;
        public:
        VAO();
        void Init();
        void LinkVBO(VBO& VBO, GLuint layout, GLuint divisor);
        void Bind();
        void UnBind();
        void Delete();
        GLuint GetID();
    };
}