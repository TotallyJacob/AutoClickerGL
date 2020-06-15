#pragma once

#include<iostream>
#include<vector>

//dependencies
#include"GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"
#include "GLM/gtx/transform.hpp"

#include"GuiManager.h"

namespace engine::gui {

	struct Range {
		float value = 0, toValue = 0;
	};

	struct GuiElement {
		unsigned int guiGeometryId = 0;
		float depth = 0;
		glm::vec3 position;
		glm::vec3 scale;
		glm::vec4 colour;
		Range xRange;
		Range yRange;
	};

	struct GuiContainer {

		void (*onUpdate)(void* manager, int x, int y);

		bool update = false;
		float depth = 0;
		glm::vec3 position;
		glm::vec3 scale;

		unsigned int num_elements = 0;

		std::vector<unsigned int> elementGeometryId;
		std::vector<unsigned int> guiGeometryInstances;
		std::vector<float> depths;
		std::vector<glm::mat4> modelMatrices;
		std::vector<glm::vec4> colours;

		std::vector<glm::vec3> positions;
		std::vector<glm::vec3> scales;

		// @TODO change name
		void setGuiGeometryIds(unsigned int num_geometry) {
			guiGeometryInstances.resize(num_geometry);
		}
		void resizeMatrices() {
			if (modelMatrices.size() < positions.size())
				modelMatrices.resize(positions.size() + modelMatrices.size());
		}
		void computeMatrices() {
			resizeMatrices();

			for (int i = 0; i < positions.size(); i++) {

				auto pos = positions.at(i);
				auto scale = scales.at(i);
				
				modelMatrices.at(i) = glm::translate(position + pos) * glm::scale(scale + this->scale);

			}
		}

		// @TODO look at r values
		void addElement(GuiElement guiElement) {

			elementGeometryId.push_back(guiElement.guiGeometryId);

			unsigned int &geometryIds = guiGeometryInstances.at(guiElement.guiGeometryId);
			geometryIds++;

			depths.push_back(guiElement.depth + this->depth);
			positions.push_back(guiElement.position);
			scales.push_back(guiElement.scale);

			colours.push_back(guiElement.colour);

			num_elements++;
		}

	};

};