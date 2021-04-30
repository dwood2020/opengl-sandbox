#version 430 core


in vec2 texCoord;

out vec4 fragColor;

uniform sampler2D tex;


void main(void) {

	fragColor = texture(tex, texCoord);

}

