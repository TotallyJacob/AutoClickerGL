#include<iostream>
#include<string>
#include<filesystem>
#include<fstream>
#include<locale>
#include<sstream>

//My imports
#include"GuiUtil.hpp"
#include"GuiGeometryParser.h"

#pragma once

namespace gui {

	class GuiGeometryReader
	{
	private:

		// @TODO handle this properly
		constexpr static const char* guiIdentifier = "guiGeo.";
		constexpr static const char* path = "C:\\Users\\Jacob\\source\\repos\\AutoClickerGL\\AutoClickerGL";
		const char* guiGeometryFile;

		std::vector<char> geometryFileData;

		void readGuiGeometryFiles();

	public:

		GuiGeometryReader(const char *guiGeometryFile, GuiGeometryParser &guiGeometryParser);
		~GuiGeometryReader() = default;

	};

};

