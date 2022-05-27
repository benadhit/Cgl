#version 440 core
out vec4 FragColor;
in vec2 outCoord;

uniform sampler2D texture1;

void main()
{
   // FragColor = vec4(outColor,1.0);
   FragColor = texture(texture1, outCoord);
}