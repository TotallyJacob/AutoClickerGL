#include<iostream>
#include<vector>

//My imports
#include"GuiUtil.hpp"
#include"GuiGEometryWriter.h"

#pragma once

namespace gui {

	class GuiGeometryParser
	{
	private:

		float* vertexData;
		unsigned int vertexDataLength = 0;

		GuiGeometryWriter* guiGeometryWriter;

	public:

		GuiGeometryParser(GuiGeometryWriter *guiGeometryWriter);
		~GuiGeometryParser() = default;

		void parseGeometry(std::vector<char>& geometry);
	};

};

