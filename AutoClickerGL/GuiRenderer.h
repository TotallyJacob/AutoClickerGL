
//dependencies
#include"GL/glew.h"
#include"GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"
#include "GLM/gtx/transform.hpp"

//My imports
#include"SHaderProgram.h"

//SSBO BINDINGS
#define GUI_DRAWINDEX_BINDING 0
#define GUI_MODELMATRIX_BINDING 1
#define GUI_DEPTH_BINDING 2
#define GUI_COLOUR_BINDING 3

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

		// @TODO remove
		float verts[12] = {
			0.f, 0.f,
			0.f, -1.0f,
			1.0f, -1.0f,

			1.0f, -1.0f,
			1.0f, 0.f,
			0.f, 0.f
		};



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
		struct DefaultSSBOs {
			//SSBOs
			SSBOData drawIndexSSBO = {};
			SSBOData modelMatrixSSBO = {};
			SSBOData depthSSBO = {};
			SSBOData colourSSBO = {};
		};

		constexpr static unsigned int persistent_map_flags = GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT;
		unsigned int defaultProgram = 0;
		DefaultSSBOs defaultSSBOS = {};
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
			glGenBuffers(1, &defaultSSBOS.drawIndexSSBO.ssbo);
			glGenBuffers(1, &defaultSSBOS.modelMatrixSSBO.ssbo);
			glGenBuffers(1, &defaultSSBOS.depthSSBO.ssbo);
			glGenBuffers(1, &defaultSSBOS.colourSSBO.ssbo);
		}
		inline void bindDefaultSSBOsToShader() {
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, GUI_DRAWINDEX_BINDING, defaultSSBOS.drawIndexSSBO.ssbo);
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, GUI_MODELMATRIX_BINDING, defaultSSBOS.modelMatrixSSBO.ssbo);
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, GUI_DEPTH_BINDING, defaultSSBOS.depthSSBO.ssbo);
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, GUI_COLOUR_BINDING, defaultSSBOS.colourSSBO.ssbo);
		}

		// @TODO remove templates for both functions
		//Util
		template<typename T>
		inline const void allocateSSBOSpace(unsigned int num_elements) const {
			glBufferStorage(GL_SHADER_STORAGE_BUFFER, sizeof(T) * num_elements, NULL, persistent_map_flags);
		}

		template<typename T>
		[[nodiscard]] inline void* genSSBOPersistentMap(unsigned int num_elements) const {
			return glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, sizeof(T) * num_elements, persistent_map_flags);
		}

	public:

		GuiRenderer();
		~GuiRenderer() = default;


		void render(float *projectionMatrix);

		//Default
		// @TODO Evaluate name of function
		inline void allocateDefaultSSBOMemory(unsigned int num_default_elements) {
			
			//Allocate drawIndex
			glBindBuffer(GL_SHADER_STORAGE_BUFFER, defaultSSBOS.drawIndexSSBO.ssbo);
			allocateSSBOSpace<unsigned int>(num_default_elements);
			defaultSSBOS.drawIndexSSBO.persistentMap = genSSBOPersistentMap<unsigned int>(num_default_elements);
			
			//Allocate modelMatrix
			glBindBuffer(GL_SHADER_STORAGE_BUFFER, defaultSSBOS.modelMatrixSSBO.ssbo);
			allocateSSBOSpace<glm::mat4>(num_default_elements);
			defaultSSBOS.modelMatrixSSBO.persistentMap = genSSBOPersistentMap<glm::mat4>(num_default_elements);
			
			//Allocate depth
			glBindBuffer(GL_SHADER_STORAGE_BUFFER, defaultSSBOS.depthSSBO.ssbo);
			allocateSSBOSpace<float>(num_default_elements);
			defaultSSBOS.depthSSBO.persistentMap = genSSBOPersistentMap<float>(num_default_elements);
			
			//Allocate Colour
			glBindBuffer(GL_SHADER_STORAGE_BUFFER, defaultSSBOS.colourSSBO.ssbo);
			allocateSSBOSpace<glm::vec4>(num_default_elements);
			defaultSSBOS.colourSSBO.persistentMap = genSSBOPersistentMap<glm::vec4>(num_default_elements);
		

			glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
		}
		inline void genDefaultVertexBuffers() {
			glGenVertexArrays(1, &renderable.vao);
			glBindVertexArray(renderable.vao);

			// @TODO change for geometry contianer (both functions)
			genVbo();
			genIndirectBuffer();

			glBindVertexArray(0);
		}
		inline void genVbo() {
			unsigned int vbo = 0;
			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);

			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, &verts, GL_STATIC_DRAW);

			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (const void*)0);
			glEnableVertexAttribArray(0);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		inline void genIndirectBuffer() {
			glGenBuffers(1, &renderable.indirectBuffer);
			glBindBuffer(GL_DRAW_INDIRECT_BUFFER, renderable.indirectBuffer);

			// @TODO properly do this!!
			// Only genning it for 1 set of geometry
#define SIZE 1
			Indirect indirect[SIZE];
			for (int i = 0; i < SIZE; i++) {
				indirect[i].count = 6; //Num of vertices
				indirect[i].instanceCount = 1; //Num of instances
				indirect[i].first = 6 * i; //Distance from the start of the indirect Buffer
				indirect[i].baseInstance = 0; //No idea
			}


			glBufferData(GL_DRAW_INDIRECT_BUFFER, sizeof(Indirect) * SIZE, &indirect[0], GL_DYNAMIC_DRAW);
#undef SIZE 
			glBindBuffer(GL_DRAW_INDIRECT_BUFFER, 0);
		}

		inline void tempFunctionToSetSSBOData() {

			renderable.drawCount = 1;

			glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(100.f, 100.f, -10.f))
				* glm::scale(glm::vec3(100.0f, 100.0f, 1.0f));

			glm::vec4 colour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

			//Mapping
			((unsigned int*)defaultSSBOS.drawIndexSSBO.persistentMap)[0] = 0;
			((glm::mat4*)defaultSSBOS.modelMatrixSSBO.persistentMap)[0] = modelMatrix;
			((float*)defaultSSBOS.depthSSBO.persistentMap)[0] = 0.f;
			((glm::vec4*)defaultSSBOS.colourSSBO.persistentMap)[0] = colour;
		}
		
	};

};

