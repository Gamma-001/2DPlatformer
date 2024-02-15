#version 330 core

in vec2 texCoord;

out vec4 fragColor;

uniform sampler2D texture0;

void main() {
    // fragColor = vec4(texCoord.x, texCoord.y, 0.5f, 1.0f);
    fragColor = texture(texture0, texCoord);
}