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

		//Default init
		inline void initDefaultShader();
		inline void genDefaultSSBOs();
		inline void bindDefaultSSBOsToShader();

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
			updatePersistentMap<ARRAY_TYPE, SIZE>(persistentMap, ssboData, numDataToCpy, persistentMapStartPoint);
		}

		template<typename ARRAY_TYPE, typename SIZE>
		inline void updatePersistentMap(ARRAY_TYPE *persistentMap, void* ssboData, const unsigned int numDataToCpy, const unsigned int persistentMapStartPoint) {
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

