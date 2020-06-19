#include<iostream>
#include<vector>

//My imports
#include"GuiUtil.hpp"
#include"GuiGeometryReader.h"

#pragma once

namespace gui {

	class GuiGeometryParser
	{
	private:

		util::GuiGeometry defaultGeometry;
		util::GuiGeometry textureGeometry;

		using SplitLine = std::vector<std::string>;
		void parse(std::vector<SplitLine> &splitLine, std::vector<std::string>& geometryFileNames);

	public:

		GuiGeometryParser();
		~GuiGeometryParser() = default;

		void parseGeometry(GuiGeometryReader &guiGeometryReader);

		//Getters
		std::vector<float>& getDefaultVertices() {
			return defaultGeometry.verts;
		}

		std::vector<util::GeometryData>& getDefaultGeometryData() {
			return defaultGeometry.geometryData;
		}

		std::vector<float>& getTextureVertices() {
			return textureGeometry.verts;
		}

		std::vector<util::GeometryData>& getTextureGeometryData() {
			return textureGeometry.geometryData;
		}

	};

};

