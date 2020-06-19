#version 460 core

out vec4 Frag;

in vec2 UV;
uniform sampler2D tex;

void main() {

	Frag = texture(tex, UV);

};