#version 410

in vec3 VertexPosition;
in vec3 VertexColor;

out vec3 Color;

void main() {
    Color = VertexColor;
    gl_Position = vec4(VertexPosition.x , VertexPosition.y , VertexPosition.z , 1.0);    
}


