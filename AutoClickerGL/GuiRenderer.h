//dependencies
#include"GL/glew.h"
#include"GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"
#include "GLM/gtx/transform.hpp"

//My imports
#include"ShaderProgram.h"
#include"GuiGeometryManager.h"

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

#pragma once

namespace engine::gui {

	class GuiRenderer
	{
	private:

		struct Indirect {
			unsigned int count = 0;
			unsigned int instanceCount = 0;
			unsigned int first = 0;
			unsigned int baseInstance = 0;
		};
		struct Renderable {

			unsigned int vao = 0;
			unsigned int indirectBuffer = 0;
			unsigned int drawCount = 0;

		};
		struct SSBOData {
			unsigned int ssbo = 0;
			void* persistentMap = 0;
		};

		constexpr static unsigned int persistent_map_flags = GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT;
		unsigned int defaultProgram = 0;
		Indirect* indirectPersistentMap = nullptr;

		SSBOData defaultSSBOS[4] = {
			SSBOData{0, nullptr}, //Draw Index
			SSBOData{0, nullptr}, //Model Matrices
			SSBOData{0, nullptr}, //Depth
			SSBOData{0, nullptr}  //colour
		};
		Renderable renderable = {};

		//Shaders
		inline void initDefaultShader() {
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

		//SSBOs
		inline void genDefaultSSBOs() {
			glGenBuffers(1, &defaultSSBOS[GUI_DRAWINDEX_ID].ssbo);
			glGenBuffers(1, &defaultSSBOS[GUI_MODELMATRIX_ID].ssbo);
			glGenBuffers(1, &defaultSSBOS[GUI_DEPTH_ID].ssbo);
			glGenBuffers(1, &defaultSSBOS[GUI_COLOUR_ID].ssbo);
		}
		inline void bindDefaultSSBOsToShader() {
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, GUI_DRAWINDEX_BINDING, defaultSSBOS[GUI_DRAWINDEX_ID].ssbo);
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, GUI_MODELMATRIX_BINDING, defaultSSBOS[GUI_MODELMATRIX_ID].ssbo);
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, GUI_DEPTH_BINDING, defaultSSBOS[GUI_DEPTH_ID].ssbo);
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, GUI_COLOUR_BINDING, defaultSSBOS[GUI_COLOUR_ID].ssbo);
		}
		inline constexpr size_t getSize(const unsigned int ssboId) const {
			switch (ssboId) {

			case GUI_DRAWINDEX_ID:
				return sizeof(unsigned int);

			case GUI_MODELMATRIX_ID:
				return sizeof(glm::mat4);

			case GUI_DEPTH_ID:
				return sizeof(float);

			case GUI_COLOUR_ID:
				return sizeof(glm::vec4);

			}

			return 0;
		}

		//Util
		template<typename T>
		inline const void allocateSSBOSpace(unsigned int num_elements, const GLenum target = GL_SHADER_STORAGE_BUFFER, const void* initialData = NULL) const {
			glBufferStorage(target, sizeof(T) * num_elements, initialData, persistent_map_flags);
		}

		template<typename T>
		[[nodiscard]] inline void* genSSBOPersistentMap(unsigned int num_elements, const GLenum target = GL_SHADER_STORAGE_BUFFER) const {
			return glMapBufferRange(target, 0, sizeof(T) * num_elements, persistent_map_flags);
		}
		
		template<typename ARRAY_TYPE, typename SIZE>
		inline void updateSSBO(unsigned int ssboId, void* ssboData, unsigned int numDataToCpy, unsigned int persistentMapStartPoint) {
			ARRAY_TYPE* persistentMap = (ARRAY_TYPE*)defaultSSBOS[ssboId].persistentMap;
			memcpy(&persistentMap[persistentMapStartPoint], ssboData, sizeof(SIZE) * numDataToCpy);
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

		//SSBO
		void allocateDefaultSSBOMemory(unsigned int num_default_elements); // @TODO Evaluate name of function
		
		void updateDrawIndexs(void* ssboData, unsigned int numDataToCpy, unsigned int persistentMapStartPoint);
		void updateModelMatrices(void* ssboData, unsigned int numDataToCpy, unsigned int persistentMapStartPoint);
		void updateDepths(void* ssboData, unsigned int numDataToCpy, unsigned int persistentMapStartPoint);
		void updateColours(void* ssboData, unsigned int numDataToCpy, unsigned int persistentMapStartPoint);
	};

};

