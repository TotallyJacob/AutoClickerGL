//My imports
#include"GuiRenderer.h"
#include"Gui.hpp"

#pragma once

namespace engine::gui {

	class GuiManager
	{
	private:
		GuiRenderer* guiRenderer;

		struct DefaultContainerData {
			std::vector<float> depth;
			std::vector<glm::vec3> position;
			std::vector<glm::vec3> scale;
		};
		struct DefaultElementData {
			std::vector<unsigned int> drawIndex;
			std::vector<float> depth;
			std::vector<float> modelMatrices;
			std::vector<float> colour;
		};
		struct DefaultElementMatrixData {
			glm::vec3 position;
			glm::vec3 scale;
		};

		unsigned int num_default_elements = 0;

		std::vector<unsigned int> geometryDatas;
		std::vector<DefaultElementMatrixData> defaultElementMatrixStore;

		DefaultElementData defaultElementData;
		DefaultContainerData defaultContainerData;

	public:

		GuiManager(GuiRenderer *guiRenderer);
		~GuiManager() = default;

		// @TODO add the stuff
		inline void setGeometryDataIds(unsigned int num_geometry) {
			geometryDatas.reserve(num_geometry);
			geometryDatas.resize(num_geometry);
		}

		inline void addGuiContainer(GuiContainer& guiContainer) {

			//Setting container data
			DefaultContainerData &containerData = defaultContainerData;
			containerData.depth.push_back(guiContainer.depth);
			containerData.position.push_back(guiContainer.position);
			containerData.scale.push_back(guiContainer.scale);

			unsigned int drawIndex = 0;

		
			for (auto element : guiContainer.elements) {

				unsigned int& num_instances = geometryDatas.at(element.guiGeometryId);
				num_instances++;
				
				defaultElementMatrixStore.push_back({ element.position , element.scale});
				
				//Inserting directly into elementData
				defaultElementData.drawIndex.push_back(drawIndex);
				defaultElementData.depth.push_back(element.depth);

				auto& colours = defaultElementData.colour;
				colours.resize(colours.size() + 4);
				memcpy(&colours[colours.size() - 4], &element.colour[0], sizeof(float) * 4);

				num_default_elements++;
				drawIndex++;
			}

		}

		inline void setMatrices() {
			glm::vec3 position = defaultContainerData.position.at(0);
			glm::vec3 scale = defaultContainerData.scale.at(0);

			for (auto store : defaultElementMatrixStore) {

				//Creating data
				glm::mat4 modelMatrix = glm::mat4(1.0f);
				modelMatrix *= glm::translate(glm::mat4(1.0f), (position + store.position)) * glm::scale(scale + store.scale);
		
				//Copying data the data
				auto& matrices = defaultElementData.modelMatrices;
				matrices.resize(matrices.size() + 16);
				memcpy(&matrices[matrices.size() - 16], &modelMatrix[0][0], 16 * sizeof(float));
			}
		}

		inline void setRendererData() {

			for (auto a : defaultElementData.modelMatrices)
				std::cout << a << std::endl;

			guiRenderer->allocateDefaultSSBOMemory(num_default_elements);

			guiRenderer->updateSSBO(GUI_DRAWINDEX_ID, defaultElementData.drawIndex.data(), num_default_elements);
			guiRenderer->updateSSBO(GUI_MODELMATRIX_ID, defaultElementData.modelMatrices.data(), num_default_elements);
			guiRenderer->updateSSBO(GUI_DEPTH_ID, defaultElementData.depth.data(), num_default_elements);
			guiRenderer->updateSSBO(GUI_COLOUR_ID, defaultElementData.colour.data(), num_default_elements);
				
			int i = 0;
			for (unsigned int  num_instances : geometryDatas) {
				guiRenderer->setIndirectBufferInstances(i, num_instances);
				i++;
			}

		}

	};

};

