#include<iostream>
#include<vector>

//dependencies
#include"GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"
#include "GLM/gtx/transform.hpp"

namespace engine::gui {

	struct GuiContainer {

		bool update = false;
		float depth = 0;
		glm::vec3 position;
		glm::vec3 scale;

	};

	struct GuiElement {
		unsigned int guiGeometryId = 0;
		float depth = 0;
		glm::vec3 position;
		glm::vec3 scale;
		glm::vec3 colour;
	};

};