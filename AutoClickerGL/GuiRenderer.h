
//dependencies
#include"GL/glew.h"

#define GUI_DEFAULT_SHADER

#pragma once

namespace engine::gui {

	class GuiRenderer
	{
	private:

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
			SSBOData ColourSSBO = {};
			SSBOData depthSSBO = {};
		};

		unsigned int defaultProgram = 0;
		DefaultSSBOs defaultSSBOS = {};
		Renderable renderable = {};

	public:

		GuiRenderer();
		~GuiRenderer() = default;


		void render(float *projectionMatrix);

		//Methods
		void allocateDefaultShaderSpace(unsigned int num_guiElements);

	};

};

