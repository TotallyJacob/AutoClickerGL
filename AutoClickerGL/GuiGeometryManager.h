#include<iostream>
#include<vector>
#include<map>

#pragma once

namespace engine::gui {


	class GuiGeometryManager
	{
	public:

		struct GeometryInfoData {
			unsigned int lengthToGeometry = 0;
			unsigned int geometryLength = 0;
			const char* geometryName = "null";
		};

	private:

		std::map<std::string, unsigned int> geometryId;
		//std::vector<std::string> geometryId;
		GeometryInfoData* geometryInfoData = nullptr;
		unsigned int geometryInfoDataSize = 0;

		float* vertexData = nullptr;
		unsigned int vertexDataSize = 0;

		bool geometryFreed = false;

		void setGeometry();

	public:

		GuiGeometryManager();
		~GuiGeometryManager();

		inline void freeGeometry() {
			delete[] vertexData;
			delete[] geometryInfoData;

			geometryFreed = true;
		}

		//Vertex data
		float* getVertexData() const {
			return vertexData;
		}
		unsigned int getVertexDataSize() const {
			return vertexDataSize;
		}

		//GeometryInfoData
		int getGeometryId(std::string geometryDataName) const {
			if(geometryId.count(geometryDataName) == 0)
				return -1;

			return geometryId.at(geometryDataName);
		}
		GeometryInfoData* getGeometryInfoData() const {
			return geometryInfoData;
		}
		unsigned int getGeometryInfoDataSize() const {
			return geometryInfoDataSize;
		}
	};

};

