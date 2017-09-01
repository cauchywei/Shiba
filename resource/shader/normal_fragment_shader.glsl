#version 330 core
#ifdef GL_ES
precision mediump float;
#endif

//varying mediump vec2    texCoord;
//uniform sampler2D texture;
out vec4 fragColor;
void main() {
    fragColor = vec4(0,1,0,1); //texture2d(texture,texCoord);
}
