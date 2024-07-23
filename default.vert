R"(#version 330 core
layout (location = 0) in vec3 offset;
layout (location = 1) in vec3 aPos;
void main()
{
   gl_Position = vec4(aPos+offset, 1.0);
})"