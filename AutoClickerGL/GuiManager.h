//My imports
#include"GuiRenderer.h"
#include"Gui.hpp"

#pragma once

namespace engine::gui {

	class GuiManager
	{
	private:
		GuiRenderer* guiRenderer;

		struct DefaultElementData {
			std::vector<unsigned int> drawIndex;
			std::vector<glm::mat4> modelMatrices;
			std::vector<float> depth;
			std::vector<glm::vec3> colour;
		};

		struct GeometryData {
			unsigned int id = 0;
			unsigned int num_instances = 0;
		};

		std::vector<GeometryData> geometryDatas;
		DefaultElementData defaultElementData;

	public:

		GuiManager(GuiRenderer *guiRenderer);
		~GuiManager() = default;

		inline void setRendererData() {

			guiRenderer->allocateDefaultSSBOMemory(2);

			guiRenderer->updateSSBO(GUI_DRAWINDEX_ID, defaultElementData.drawIndex.data(), defaultElementData.drawIndex.size());
			guiRenderer->updateSSBO(GUI_MODELMATRIX_ID, defaultElementData.modelMatrices.data(), defaultElementData.modelMatrices.size());
			guiRenderer->updateSSBO(GUI_DEPTH_ID, defaultElementData.depth.data(), defaultElementData.depth.size());
			guiRenderer->updateSSBO(GUI_COLOUR_ID, defaultElementData.colour.data(), defaultElementData.colour.size());
				
			for(auto geometryData : geometryDatas)
				guiRenderer->setIndirectBufferInstances(geometryData.id, geometryData.num_instances);
		}

	};

};

