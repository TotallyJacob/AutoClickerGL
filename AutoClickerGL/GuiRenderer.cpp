#include "GuiRenderer.h"

using namespace engine::gui;

GuiRenderer::GuiRenderer(GuiGeometryManager* guiGeometryManager) {

	//Default SSBOs
	initDefaultShader();
	initRenderingBuffers(guiGeometryManager);
	genDefaultSSBOs();
	bindDefaultSSBOsToShader();

	// @TODO this is temp, remove in future
	//allocateDefaultSSBOMemory(1);
	//tempFunctionToSetSSBOData();
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

//Default 
void GuiRenderer::allocateDefaultSSBOMemory(unsigned int num_default_elements) {
	//Allocate drawIndex
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, defaultSSBOS[GUI_DRAWINDEX_ID].ssbo);
	allocateSSBOSpace<unsigned int>(num_default_elements);
	defaultSSBOS[GUI_DRAWINDEX_ID].persistentMap = genSSBOPersistentMap<unsigned int>(num_default_elements);

	//Allocate modelMatrix
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, defaultSSBOS[GUI_MODELMATRIX_ID].ssbo);
	allocateSSBOSpace<glm::mat4>(num_default_elements);
	defaultSSBOS[GUI_MODELMATRIX_ID].persistentMap = genSSBOPersistentMap<glm::mat4>(num_default_elements);

	//Allocate depth
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, defaultSSBOS[GUI_DEPTH_ID].ssbo);
	allocateSSBOSpace<float>(num_default_elements);
	defaultSSBOS[GUI_DEPTH_ID].persistentMap = genSSBOPersistentMap<float>(num_default_elements);

	//Allocate Colour
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, defaultSSBOS[GUI_COLOUR_ID].ssbo);
	allocateSSBOSpace<glm::vec4>(num_default_elements);
	defaultSSBOS[GUI_COLOUR_ID].persistentMap = genSSBOPersistentMap<glm::vec4>(num_default_elements);


	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

//Buffers
void GuiRenderer::initRenderingBuffers(GuiGeometryManager* guiGeometryManager) {
	glGenVertexArrays(1, &renderable.vao);
	glBindVertexArray(renderable.vao);

	// @TODO change for geometry contianer (both functions)
	genVbo(guiGeometryManager->getVertexData(), guiGeometryManager->getVertexDataSize());
	genIndirectBuffer(guiGeometryManager->getGeometryInfoData(), guiGeometryManager->getGeometryInfoDataSize());

	glBindVertexArray(0);
}
void GuiRenderer::genVbo(float* vertices, unsigned int verticesSize) {
	unsigned int vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * verticesSize, &vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (const void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void GuiRenderer::genIndirectBuffer(GuiGeometryManager::GeometryInfoData* geometryInfoData, unsigned int geometryInfoDataSize) {
	glGenBuffers(1, &renderable.indirectBuffer);
	glBindBuffer(GL_DRAW_INDIRECT_BUFFER, renderable.indirectBuffer);

	renderable.drawCount = geometryInfoDataSize;

	Indirect* indirect = new Indirect[geometryInfoDataSize];
	for (int i = 0; i < geometryInfoDataSize; i++) {

		GuiGeometryManager::GeometryInfoData infoData = geometryInfoData[i];

		indirect[i].count = infoData.geometryLength; //Num of vertices
		indirect[i].instanceCount = 1; //Num of instances
		indirect[i].first = infoData.lengthToGeometry; //Distance from the start of the indirect Buffer
		indirect[i].baseInstance = 0; //No idea
	}

	allocateSSBOSpace<Indirect>(geometryInfoDataSize, GL_DRAW_INDIRECT_BUFFER, &indirect[0]);
	indirectPersistentMap = (Indirect*)genSSBOPersistentMap<Indirect>(geometryInfoDataSize, GL_DRAW_INDIRECT_BUFFER);

	glBindBuffer(GL_DRAW_INDIRECT_BUFFER, 0);

	delete[] indirect;
}