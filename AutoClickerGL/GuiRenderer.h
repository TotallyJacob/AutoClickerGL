#pragma once

//dependencies
#include"GL/glew.h"
#include"GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"
#include "GLM/gtx/transform.hpp"

//My imports
#include"ShaderProgram.h"
#include"GuiGeometryManager.h"
#include"GuiRendererUtil.h"

//SSBO BINDINGS
#define GUI_DRAWINDEX_BINDING 0
#define GUI_MODELMATRIX_BINDING 1
#define GUI_DEPTH_BINDING 2
#define GUI_COLOUR_BINDING 3

//IDs
#define GUI_DRAWINDEX_ID 0
#define GUI_MODELMATRIX_ID 1
#define GUI_DEPTH_ID 2
#define GUI_COLOUR_ID 3

//SSBO block names
#define GUI_DRAWINDEX_NAME "gui_drawIndex"
#define GUI_MODELMATRIX_NAME "gui_modelMatrix"
#define GUI_DEPTH_NAME "gui_depth"
#define GUI_COLOUR_NAME "gui_colour"

namespace engine::gui {

	class GuiRenderer
	{
	private:

		unsigned int defaultProgram = 0;
		util::Indirect* indirectPersistentMap = nullptr;
		util::SSBOData defaultSSBOS[4] = {
			util::SSBOData{0, nullptr}, //Draw Index
			util::SSBOData{0, nullptr}, //Model Matrices
			util::SSBOData{0, nullptr}, //Depth
			util::SSBOData{0, nullptr}  //colour
		};
		util::Renderable renderable = {};

		//Default init
		inline void initDefaultShader();
		inline void genDefaultSSBOs();
		inline void bindDefaultSSBOsToShader();

		template<typename ARRAY_TYPE, typename SIZE>
		inline void updateSSBO(unsigned int ssboId, void* ssboData, unsigned int numDataToCpy, unsigned int persistentMapStartPoint) {
			ARRAY_TYPE* persistentMap = (ARRAY_TYPE*)defaultSSBOS[ssboId].persistentMap;
			util::updatePersistentMap<ARRAY_TYPE, SIZE>(persistentMap, ssboData, numDataToCpy, persistentMapStartPoint);
		}

		//Default
		void initRenderingBuffers(GuiGeometryManager* guiGeometryManager);
		void genVbo(float* vertices, unsigned int verticesSize);
		void genIndirectBuffer(GuiGeometryManager::GeometryInfoData* geometryInfoData, unsigned int geometryInfoDataSize);
	
	public:

		GuiRenderer(GuiGeometryManager *guiGeometryManager);
		~GuiRenderer() = default;

		void render(float *projectionMatrix);

		//Indirect
		inline void setIndirectBufferInstances(unsigned int geometryId, unsigned int num_instances) {
			indirectPersistentMap[geometryId].instanceCount = num_instances;
		}
		void updateIndirectBuffer(void* data, unsigned int numIndirectBuffer, unsigned int persistentMapStartPoint);

		//SSBO setters
		void allocateDefaultSSBOMemory(unsigned int num_default_elements); // @TODO Evaluate name of function
		
		void updateDrawIndexs(void* ssboData, unsigned int numDataToCpy, unsigned int persistentMapStartPoint);
		void updateModelMatrices(void* ssboData, unsigned int numDataToCpy, unsigned int persistentMapStartPoint);
		void updateDepths(void* ssboData, unsigned int numDataToCpy, unsigned int persistentMapStartPoint);
		void updateColours(void* ssboData, unsigned int numDataToCpy, unsigned int persistentMapStartPoint);

		//SSBO getters
		const float* getColours() const {
			return (float*)defaultSSBOS[GUI_COLOUR_ID].persistentMap;
		}
	};

};

