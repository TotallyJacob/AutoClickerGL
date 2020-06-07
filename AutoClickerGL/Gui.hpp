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

		std::vector<GuiElement> elements;

		// @TODO look at r values
		void addElement(GuiElement guiElement) {
			elements.push_back(guiElement);
		}

	};

};