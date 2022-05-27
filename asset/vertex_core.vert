#version 440 core

layout (location =0) in vec3 aPos;
layout (location =1) in vec2 aTextureCoord;

out vec3 outColor;
out vec2 outCoord;

uniform mat4 transform;


void main()
{
    gl_Position = transform * vec4(aPos, 1.0);
    outCoord = aTextureCoord;
}