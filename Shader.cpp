#include "Shader.hpp"
namespace Graphics
{
    std::string Shader::GetFileContent(std::string filename)
    {
        std::ifstream file(filename, std::ios::binary); // открываем файл в бинарном режиме
        if(file)
        {
            std::string content;
            file.seekg(0, std::ios::end); 
            content.resize(file.tellg()); //  изменяем размер строки под размер файла
            file.seekg(0, std::ios::beg);
            file.read(&content[0], content.size()); // считываем из файла в строку
            file.close();
            return content;
        }
        throw errno;
    }
    void Shader::Init(std::string vertFile, std::string fragFile)
    {
        // Счиьываем код шейдеров
        std::string VertCode = GetFileContent(vertFile);
        std::string FragCode = GetFileContent(fragFile);
        const char* VertSource = VertCode.c_str();
        const char* FragSource = FragCode.c_str();
        // Работа с вершинным шейдером
        GLuint VertShader = glCreateShader(GL_VERTEX_SHADER); // создаем объект шейдера
        glShaderSource(VertShader, 1, &VertSource, NULL); // передаем туда код шейдера
        glCompileShader(VertShader); // компилуруем шейдер
        // Работа с фрагментным шейдером
        GLuint FragShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(FragShader, 1, &FragSource, NULL);
        glCompileShader(FragShader);

        ID = glCreateProgram(); // создание шейдерной программы
        glAttachShader(ID, VertShader); // привязка вершинного шейдера 
        glAttachShader(ID, FragShader); // привязка фрагментного шейдера
        glLinkProgram(ID); // линковка
        
        // удаление ненужных(уже) шейдеров
        glDeleteShader(VertShader); 
        glDeleteShader(FragShader);
    }

    void Shader::Activate()
    {
        glUseProgram(ID);
        vertColorLocation = glGetUniformLocation(ID, "OurColor");
    }

    void Shader::Delete()
    {
        glDeleteProgram(ID);
    }
    GLuint Shader::GetID()
    {
        return ID;
    }
    void Shader::SetColor(RGBColor color)
    {
        glUniform4f(vertColorLocation, color.r, color.g, color.b, 1.0f);
    }
    Shader::Shader(): ID(0) {}
}