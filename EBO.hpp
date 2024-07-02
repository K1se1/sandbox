#pragma once
#include "C:/msys64/mingw64/lib/glad/include/glad/glad.h"


namespace Graphics
{
    class EBO
    {
    private:
        GLuint ID;
    public:
        EBO(GLuint* indices, GLsizeiptr size);
        void Bind();
        void UnBind();
        void Delete();
        GLuint GetID();

    };
}