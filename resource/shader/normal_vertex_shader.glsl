#version 330 core
#ifdef GL_ES
precision mediump float;
#endif

layout(location = 0) in vec3    vertex;
layout(location = 1) in vec3    normal;
//in mediump vec2  texture;

uniform mat4    transformMatrix;
uniform mat4    viewMatrix;
uniform mat4    projectionMatrix;

//varying mediump vec2    texCoord;

void main() {
    vec4 worldPosition = transformMatrix * vec4(vertex, 1.0);
    vec4 positionRelativeToCam = viewMatrix * worldPosition;
    gl_Position = projectionMatrix * positionRelativeToCam;

//    gl_Position = vec4(vertex, 1.0);
//    texCoord = texture.xy;
}
