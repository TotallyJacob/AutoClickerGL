#pragma once

namespace engine::gui {


	class GuiGeometryManager
	{
	private:

		struct GeometryData {
			unsigned int lengthToGeometry = 0;
			unsigned int geometryLength = 0;
		};

		float* vertexData;

	public:

		GuiGeometryManager();
		~GuiGeometryManager() = default;

		inline void addGeometry(char *fileData) {
			#include"GuiGeometry.hpp"
			this->vertexData = vertexData;
		}

		float* getVertexData() const {
			return vertexData;
		}

	};

};

