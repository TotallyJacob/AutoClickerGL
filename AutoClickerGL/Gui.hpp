#include<iostream>
#include<vector>

//dependencies
#include"GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"
#include "GLM/gtx/transform.hpp"

namespace engine::gui {

	struct GuiElement {
		unsigned int guiGeometryId = 0;
		float depth = 0;
		glm::vec3 position;
		glm::vec3 scale;
		glm::vec4 colour;
	};

	struct GuiContainer {

		bool update = false;
		float depth = 0;
		glm::vec3 position;
		glm::vec3 scale;

		std::vector<unsigned int> guiGeometryIds;
		std::vector<float> depths;
		std::vector<glm::mat4> modelMatrices;
		std::vector<glm::vec4> colours;

		std::vector<glm::vec3> positions;
		std::vector<glm::vec3> scales;

		std::vector<GuiElement> elements;

		// @TODO change name
		void setGuiGeometryIds(unsigned int num_geometry) {
			guiGeometryIds.resize(num_geometry);
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

			unsigned int &geometryIds = guiGeometryIds.at(guiElement.guiGeometryId);
			geometryIds++;

			depths.push_back(guiElement.depth + this->depth);
			positions.push_back(guiElement.position);
			scales.push_back(guiElement.scale);

			colours.push_back(guiElement.colour);

			elements.push_back(guiElement);
		}

	};

};