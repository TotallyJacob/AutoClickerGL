#version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 uv;

uniform mat4 projectionMatrix;

layout(std430, binding = 0) buffer gui_drawIndex {
	unsigned int drawIndex[];
};

layout(std430, binding = 1) buffer gui_modelMatrix {
	mat4 modelMatrix[];
};

layout(std430, binding = 2) buffer gui_depth {
	float depth[];
};

layout(std430, binding = 3) buffer gui_colour {
	vec4 colour[];
};

out vec2 UV;

void main() {

	unsigned int id = drawIndex[gl_DrawID + gl_InstanceID + gl_BaseInstance];

	UV = uv;

	gl_Position = projectionMatrix * modelMatrix[id] * vec4(vec2(position.x, position.z), depth[id], 1.0f);
};s