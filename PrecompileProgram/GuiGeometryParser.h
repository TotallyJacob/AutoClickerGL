#include<iostream>
#include<vector>

//My imports
#include"GuiUtil.hpp"

#pragma once

namespace gui {

	class GuiGeometryParser
	{
	private:

		float* vertexData;
		unsigned int vertexDataLength = 0;

	public:
		GuiGeometryParser() = default;
		~GuiGeometryParser() = default;

		void parseGeometry(std::vector<char>& geometry);
	};

};

