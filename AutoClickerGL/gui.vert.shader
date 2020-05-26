#version 460 core

layout(location = 0) in vec2 position;

uniform mat4 projectionMatrix;

layout(std430, binding = 0) buffer gui_modelMatrix {
	mat4 modelMatrix[];
};

layout(std430, binding = 0) buffer gui_drawIndex {
	mat4 drawIndex[];
};

layout(std430, binding = 0) buffer gui_colour {
	mat4 colour[];
};

layout(std430, binding = 0) buffer gui_depth {
	mat4 depth[];
};

out vec4 fragOut;

void main(){

	unsigned int id = drawIndex[gl_DrawId];

	fragOut = colour[id];

	gl_Position = projectionMatrix * modelMatrix[id] * vec4(position, depth[id], 1.0f);
};