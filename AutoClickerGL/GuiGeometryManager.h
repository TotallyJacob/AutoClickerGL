#pragma once

namespace engine::gui {


	class GuiGeometryManager
	{
	private:

		struct GeometryData {
			unsigned int lengthToGeometry = 0;
			unsigned int geometryLength = 0;
		};

		float* vertexData = nullptr;
		unsigned int vertexDataSize = 0;

	public:

		GuiGeometryManager();
		~GuiGeometryManager() = default;

		inline void setGeometry() {
			//Data in here to go out of scope
			#include"GuiGeometry.hpp"

			this->vertexDataSize = vertexDataSize;
			this->vertexData = new float[vertexDataSize];

			//memcpy(this->vertexData, vertexData, sizeof(float) * vertexDataSize);
		}

		inline void freeGeometry() {
			delete[] vertexData;
		}

		float* getVertexData() const {
			return vertexData;
		}

	};

};

