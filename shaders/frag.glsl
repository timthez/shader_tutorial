#version 410

in vec3 Color;
uniform float timer;
uniform vec2 screen;
//in vec4 gl_FradCoord;
out vec4 FragColor;

void main() {
    FragColor = vec4(1.0,0.0,0.0,1.0);
}