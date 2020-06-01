#include<iostream>
#include<vector>

//My imports
#include"GuiUtil.hpp"

#pragma once

namespace gui {

	class GuiGeometryWriter
	{
	private:
		constexpr static const char* guiGeometryPath = "C:\\Users\\Jacob\\source\\repos\\AutoClickerGL\\AutoClickerGL\\GuiGeometry.hpp";

	public:

		struct GeometryData {
			unsigned int num_verts = 0;
			unsigned int floatsFromStartOfGeometry = 0;
		};

		GuiGeometryWriter() = default;
		~GuiGeometryWriter() = default;

		void writeGeometry(std::vector<float>& geometry, std::vector<GeometryData>& geometryData);
	};

};

