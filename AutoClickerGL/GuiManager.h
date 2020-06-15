#pragma once

#include<iostream>
#include<chrono>

//My imports
#include"GuiRenderer.h"
#include"Gui.hpp"


namespace engine::gui {

	class GuiManager
	{
	private:
		GuiRenderer* guiRenderer;

		//Default
		struct DefaultContainerData {
			std::vector<float> depth;
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
		bool updateDefaultColours = false;

		std::vector<unsigned int> geometryDatas;
		std::vector<DefaultElementMatrixData> defaultElementMatrixStore;
		std::vector<void (*)(void* manager, int x, int y)> defaultContainerUpdate;

		DefaultElementData defaultElementData;
		DefaultContainerData defaultContainerData;

	public:

		GuiManager(GuiRenderer *guiRenderer);
		~GuiManager() = default;

		// @TODO add the stuff
		inline void setGeometryDataIds(unsigned int num_geometry) {
			geometryDatas.resize(num_geometry);
		}

		inline void addGuiContainer(GuiContainer& guiContainer) {

			using std::chrono::duration_cast;
			using std::chrono::nanoseconds;
			typedef std::chrono::high_resolution_clock clock;

			guiContainer.computeMatrices();

			auto start = clock::now();

			//Setting container data
			DefaultContainerData &containerData = defaultContainerData;
			containerData.depth.push_back(guiContainer.depth);

			if(guiContainer.update)
				defaultContainerUpdate.push_back(guiContainer.onUpdate);

			unsigned int drawIndex = 0;
			
			for (int i = 0; i < geometryDatas.size(); i++) {
				unsigned int& current = geometryDatas.at(i);
				current += guiContainer.guiGeometryIds.at(i);
			}

			auto& depth = defaultElementData.depth;
			depth.resize(depth.size() + guiContainer.depths.size());
			memcpy(&depth[depth.size() - guiContainer.depths.size()], guiContainer.depths.data(), sizeof(float) * guiContainer.depths.size());
		
			auto& colours = defaultElementData.colour;
			colours.resize(colours.size() + (guiContainer.colours.size() * 4));
			memcpy(&colours[colours.size() - (guiContainer.colours.size() * 4)], &guiContainer.colours[0], sizeof(float) * 4 * guiContainer.colours.size());
			
			//guiContainer.computeMatrices();
			auto& modelMatrices = defaultElementData.modelMatrices;
			modelMatrices.resize(modelMatrices.size() + (guiContainer.modelMatrices.size() * 16));
			memcpy(&modelMatrices[modelMatrices.size() - (guiContainer.modelMatrices.size() * 16)], &guiContainer.modelMatrices[0][0], sizeof(float) * 16 * guiContainer.modelMatrices.size());

			for (int i = 0; i < guiContainer.num_elements; i++) {
				
				defaultElementData.drawIndex.push_back(drawIndex);

				num_default_elements++;
				drawIndex++;
			}

			auto end = clock::now();
			std::cout << duration_cast<nanoseconds>(end - start).count() << "ns\n";

		}

		inline void setRendererData() {

			guiRenderer->allocateDefaultSSBOMemory(num_default_elements);

			guiRenderer->updateDrawIndexs(defaultElementData.drawIndex.data(), num_default_elements, 0);
			guiRenderer->updateModelMatrices(defaultElementData.modelMatrices.data(), num_default_elements, 0);
			guiRenderer->updateDepths(defaultElementData.depth.data(), num_default_elements, 0);
			guiRenderer->updateColours(defaultElementData.colour.data(), num_default_elements, 0);
				
			int i = 0;
			for (unsigned int  num_instances : geometryDatas) {
				guiRenderer->setIndirectBufferInstances(i, num_instances);
				i++;
			}

		}

		// @TODO temp stuff
		float elementColour(const unsigned int id, const unsigned int value) const {
			return defaultElementData.colour.at((id * 4) + value);
		}

		bool updatingColours() const {
			return updateDefaultColours;
		}

		inline void updateColours() {
			if (updateDefaultColours) {
				guiRenderer->updateColours(defaultElementData.colour.data(), num_default_elements, 0);
				//std::cout << "updated colours" << std::endl;
				updateDefaultColours = false;
			}
		}

		inline void setColour(unsigned int elementId, glm::vec4 colour) {
			float *start = &defaultElementData.colour.at(elementId * 4);
			memcpy(start, &colour[0], sizeof(float) * 4);
			updateDefaultColours = true;
		}

		inline void updateContainers(unsigned int mouseX, unsigned int mouseY) {
			for (auto function : defaultContainerUpdate) {
				function(this, mouseX, mouseY);
			}

		}

	};

};

