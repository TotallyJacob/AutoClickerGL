#include<iostream>

#pragma once

namespace engine::gui {


	class GuiGeometryManager
	{
	public:

		struct GeometryInfoData {
			unsigned int lengthToGeometry = 0;
			unsigned int geometryLength = 0;
		};

		GuiGeometryManager();
		~GuiGeometryManager();

		inline void freeGeometry() {
			delete[] vertexData;
			delete[] geometryInfoData;

			geometryFreed = true;
		}

		float* getVertexData() const {
			return vertexData;
		}

		unsigned int getVertexDataSize() const {
			return vertexDataSize;
		}

		GeometryInfoData* getGeometryInfoData() const {
			return geometryInfoData;
		}

		unsigned int getGeometryInfoDataSize() const {
			return geometryInfoDataSize;
		}

	private:

		GeometryInfoData* geometryInfoData = nullptr;
		unsigned int geometryInfoDataSize = 0;

		float* vertexData = nullptr;
		unsigned int vertexDataSize = 0;

		bool geometryFreed = false;

		void setGeometry();
	};

};

