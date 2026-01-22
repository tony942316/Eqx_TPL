#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
    TexCoord = aTexCoord;
    gl_Position = proj * view * model * vec4(aPos, 0.0f, 1.0f);
}
