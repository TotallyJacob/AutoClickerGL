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
		struct Range {
			unsigned int start = 0;
			unsigned int end = 0;
		};
		struct DefaultContainerData {
			std::vector<Range> range;
			std::vector<float> depth;
			std::vector<glm::vec3> position;
			std::vector<std::vector<unsigned int>> instancesPerGeometry;
			std::vector<std::vector<unsigned int>> elementGeometryIds;
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

		unsigned int num_containers = 0;
		unsigned int num_default_elements = 0;
		bool updateDefaultColours = false;

		DefaultElementData defaultElementData;
		DefaultContainerData defaultContainerData;
		std::vector<unsigned int> defaultInstancesPerGeometry;
		std::vector<void (*)(void* manager, int x, int y)> defaultContainerUpdate;

	public:

		GuiManager(GuiRenderer *guiRenderer);
		~GuiManager() = default;

		// @TODO add the stuff
		inline void setGeometryDataIds(unsigned int num_geometry) {
			defaultInstancesPerGeometry.resize(num_geometry);
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
			containerData.position.push_back(guiContainer.position);
			containerData.instancesPerGeometry.push_back(guiContainer.guiGeometryInstances);
			containerData.elementGeometryIds.push_back(guiContainer.elementGeometryId);
			
			Range range = {};
			range.start = num_default_elements;
			num_default_elements += guiContainer.num_elements;
			range.end = num_default_elements;

			containerData.range.push_back(range); //How many elements currently added to the arrays
			//

			if(guiContainer.update)
				defaultContainerUpdate.push_back(guiContainer.onUpdate);
			
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

			auto end = clock::now();
			std::cout << duration_cast<nanoseconds>(end - start).count() << "ns\n";

			num_containers++;
		}

		inline void setDrawIndexs() {
			std::vector<unsigned int>& drawIndexs = defaultElementData.drawIndex;

			for (int index = 0; index < num_containers; index++) {

				std::vector<unsigned int>& geometryIds = defaultContainerData.elementGeometryIds.at(index);

				Range &containersElementIndexRange = defaultContainerData.range.at(index);

				for (unsigned int elementId = 0; elementId < geometryIds.size(); elementId++) {

					unsigned int elementsGeometryId = geometryIds.at(elementId); 

					elementId += containersElementIndexRange.start; //ActualElement id -> not just relative to the container

					drawIndexs.insert(drawIndexs.begin() + defaultInstancesPerGeometry.at(elementsGeometryId), elementId);

					defaultInstancesPerGeometry.at(elementsGeometryId) += 1; // increasing the defaultInstances per geometry
				}

			}
		}
		inline void setRendererData() {

			guiRenderer->allocateDefaultSSBOMemory(num_default_elements);

			guiRenderer->updateDrawIndexs(defaultElementData.drawIndex.data(), num_default_elements, 0);
			guiRenderer->updateModelMatrices(defaultElementData.modelMatrices.data(), num_default_elements, 0);
			guiRenderer->updateDepths(defaultElementData.depth.data(), num_default_elements, 0);
			guiRenderer->updateColours(defaultElementData.colour.data(), num_default_elements, 0);
				
			int i = 0;
			for (unsigned int  num_instances : defaultInstancesPerGeometry) {
				guiRenderer->setIndirectBufferInstances(i, num_instances);
				i++;
			}

		}

		// @TODO temp stuff
		float elementColour(const unsigned int id, const unsigned int value) const {
			return guiRenderer->getColours()[(id * 4) + value];
		}

		inline void setColour(unsigned int elementId, glm::vec4 colour) {
			guiRenderer->updateColours(&colour[0], num_default_elements, elementId * 4);
		}

		inline void updateContainers(unsigned int mouseX, unsigned int mouseY) {
			for (auto function : defaultContainerUpdate) {
				function(this, mouseX, mouseY);
			}

		}

	};

};

