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
		GuiGeometryWriter() = default;
		~GuiGeometryWriter() = default;

		void writeGeometry(std::vector<float>& geometry);
	};

};

