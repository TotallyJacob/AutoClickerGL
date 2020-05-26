#include "GuiRenderer.h"

using namespace engine::gui;

GuiRenderer::GuiRenderer() {

}

void GuiRenderer::render(float *projectionMatrix){

	/*
		Basic drawing layout
	*/


	//binding
	glUseProgram(defaultProgram);
	glBindVertexArray(renderable.vao);
	glBindBuffer(GL_DRAW_INDIRECT_BUFFER, renderable.indirectBuffer);

	glUniformMatrix4fv(glGetUniformLocation(defaultProgram, "projectionMatrix"), 1, false, projectionMatrix);

	//Drawing
	glMultiDrawArraysIndirect(GL_TRIANGLES, 0, renderable.drawCount, 0);

	//Unbinding
	glBindBuffer(GL_DRAW_INDIRECT_BUFFER, 0);
	glBindVertexArray(0);
	glUseProgram(0);

}