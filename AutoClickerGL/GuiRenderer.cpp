#include "GuiRenderer.h"

using namespace engine::gui;

GuiRenderer::GuiRenderer(GuiGeometryManager* guiGeometryManager) {

	//Default SSBOs
	initDefaultShader();
	initRenderingBuffers(guiGeometryManager);
	genDefaultSSBOs();
	bindDefaultSSBOsToShader();

}

void GuiRenderer::render(float *projectionMatrix){
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
	util::allocateSSBOSpace<unsigned int>(num_default_elements);
	defaultSSBOS[GUI_DRAWINDEX_ID].persistentMap = util::genSSBOPersistentMap<unsigned int>(num_default_elements);

	//Allocate modelMatrix
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, defaultSSBOS[GUI_MODELMATRIX_ID].ssbo);
	util::allocateSSBOSpace<glm::mat4>(num_default_elements);
	defaultSSBOS[GUI_MODELMATRIX_ID].persistentMap = util::genSSBOPersistentMap<glm::mat4>(num_default_elements);

	//Allocate depth
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, defaultSSBOS[GUI_DEPTH_ID].ssbo);
	util::allocateSSBOSpace<float>(num_default_elements);
	defaultSSBOS[GUI_DEPTH_ID].persistentMap = util::genSSBOPersistentMap<float>(num_default_elements);

	//Allocate Colour
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, defaultSSBOS[GUI_COLOUR_ID].ssbo);
	util::allocateSSBOSpace<glm::vec4>(num_default_elements);
	defaultSSBOS[GUI_COLOUR_ID].persistentMap = util::genSSBOPersistentMap<glm::vec4>(num_default_elements);


	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

//SSBOS
void GuiRenderer::genDefaultSSBOs() {
	glGenBuffers(1, &defaultSSBOS[GUI_DRAWINDEX_ID].ssbo);
	glGenBuffers(1, &defaultSSBOS[GUI_MODELMATRIX_ID].ssbo);
	glGenBuffers(1, &defaultSSBOS[GUI_DEPTH_ID].ssbo);
	glGenBuffers(1, &defaultSSBOS[GUI_COLOUR_ID].ssbo);
}
void GuiRenderer::bindDefaultSSBOsToShader() {
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, GUI_DRAWINDEX_BINDING, defaultSSBOS[GUI_DRAWINDEX_ID].ssbo);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, GUI_MODELMATRIX_BINDING, defaultSSBOS[GUI_MODELMATRIX_ID].ssbo);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, GUI_DEPTH_BINDING, defaultSSBOS[GUI_DEPTH_ID].ssbo);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, GUI_COLOUR_BINDING, defaultSSBOS[GUI_COLOUR_ID].ssbo);
}

//Shaders
void GuiRenderer::initDefaultShader() {
	ShaderProgram program({ "gui.vert.shader","gui.frag.shader" });
	defaultProgram = program;

	//Finding block binding indexs
	unsigned int drawIndex_binding = glGetProgramResourceIndex(defaultProgram, GL_SHADER_STORAGE_BUFFER, GUI_DRAWINDEX_NAME);
	unsigned int modelMatrix_binding = glGetProgramResourceIndex(defaultProgram, GL_SHADER_STORAGE_BUFFER, GUI_MODELMATRIX_NAME);
	unsigned int depth_binding = glGetProgramResourceIndex(defaultProgram, GL_SHADER_STORAGE_BUFFER, GUI_DEPTH_NAME);
	unsigned int colour_binding = glGetProgramResourceIndex(defaultProgram, GL_SHADER_STORAGE_BUFFER, GUI_COLOUR_NAME);

	//Setting Binding blocks
	glShaderStorageBlockBinding(defaultProgram, drawIndex_binding, GUI_DRAWINDEX_BINDING);
	glShaderStorageBlockBinding(defaultProgram, modelMatrix_binding, GUI_MODELMATRIX_BINDING);
	glShaderStorageBlockBinding(defaultProgram, depth_binding, GUI_DEPTH_BINDING);
	glShaderStorageBlockBinding(defaultProgram, colour_binding, GUI_COLOUR_BINDING);
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

	using Indirect = util::Indirect;
	Indirect* indirect = new Indirect[geometryInfoDataSize];

	for (int i = 0; i < geometryInfoDataSize; i++) {

		GuiGeometryManager::GeometryInfoData infoData = geometryInfoData[i];

		indirect[i].count = (infoData.geometryLength/3); //Num of vertices
		indirect[i].instanceCount = 1; //Num of instances
		indirect[i].first = infoData.lengthToGeometry; //Distance from the start of the indirect Buffer
		indirect[i].baseInstance = 0; //No idea
	}

	util::allocateSSBOSpace<Indirect>(geometryInfoDataSize, GL_DRAW_INDIRECT_BUFFER, &indirect[0]);
	this->indirectPersistentMap = (Indirect*)util::genSSBOPersistentMap<Indirect>(geometryInfoDataSize, GL_DRAW_INDIRECT_BUFFER);

	glBindBuffer(GL_DRAW_INDIRECT_BUFFER, 0);

	delete[] indirect;
}

//Updating buffers
void GuiRenderer::updateIndirectBuffer(void* data, unsigned int numIndirectBuffer, unsigned int persistentMapStartPoint) {
	using Indirect = util::Indirect;
	util::updatePersistentMap<Indirect, Indirect>(indirectPersistentMap, data, numIndirectBuffer, persistentMapStartPoint);
}
void GuiRenderer::updateDrawIndexs(void* ssboData, unsigned int numDataToCpy, unsigned int persistentMapStartPoint) {
	updateSSBO<unsigned int, unsigned int>(GUI_DRAWINDEX_ID, ssboData, numDataToCpy, persistentMapStartPoint);
}
void GuiRenderer::updateModelMatrices(void* ssboData, unsigned int numDataToCpy, unsigned int persistentMapStartPoint) {
	updateSSBO<float, glm::mat4>(GUI_MODELMATRIX_ID, ssboData, numDataToCpy, persistentMapStartPoint);
}
void GuiRenderer::updateDepths(void* ssboData, unsigned int numDataToCpy, unsigned int persistentMapStartPoint) {
	updateSSBO<float, float>(GUI_DEPTH_ID, ssboData, numDataToCpy, persistentMapStartPoint);
}
void GuiRenderer::updateColours(void* ssboData, unsigned int numDataToCpy, unsigned int persistentMapStartPoint) {
	updateSSBO<float, glm::vec4>(GUI_COLOUR_ID, ssboData, numDataToCpy, persistentMapStartPoint);
}