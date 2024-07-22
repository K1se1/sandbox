#pragma once
#include "../glad/glad.h"


namespace Graphics
{
    // Класс для индексного буффера
    class EBO
    {
    private:
        GLuint ID;
    public:
        EBO();
        void Init(GLuint* indices, GLsizeiptr size);
        void Bind();
        void UnBind();
        void Delete();
        GLuint GetID();

    };
}