#include<iostream>
#include<string>
#include<filesystem>
#include<fstream>
#include<locale>
#include<sstream>

//My imports
#include"GuiUtil.hpp"

#pragma once

namespace gui {

	class GuiGeometryLoader
	{
	private:

		// @TODO handle this properly
		constexpr static const char* guiIdentifier = "guiGeo.";
		constexpr static const char* path = "C:\\Users\\Jacob\\source\\repos\\AutoClickerGL\\AutoClickerGL";
		const char* guiGeometryFile;

		//Vertex Data
		float* vertexData;
		unsigned int vertexDataLength = 0;

		inline const void getGuiGeometryFiles(std::vector<std::wstring>& filePaths) const;

	public:

		GuiGeometryLoader(const char *guiGeometryFile);
		~GuiGeometryLoader() = default;

	};

};

