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
		constexpr static unsigned int guiIdentifierLength = 7;
		constexpr static const char* path = "C:\\Users\\Jacob\\source\\repos\\AutoClickerGL\\AutoClickerGL";
		const char* guiGeometryFile;

		std::vector<char> geometryFileData;
		std::vector<std::string> geometryFileNames;


		inline static void readGuiGeometryData(std::wstring filePath, std::vector<char>& data, unsigned int geometryIndex) {
			std::ifstream file(filePath, std::ios::binary);
			std::streambuf* raw_buffer = file.rdbuf();

			file.seekg(0, std::ios::end);
			unsigned int fileLength = file.tellg();
			file.seekg(0, std::ios::beg);

			char* buff = new char[fileLength];

			raw_buffer->sgetn(buff, fileLength);

			file.close();

			// @TODO make better

			bool addLineToData = true;

			for (int i = 0; i < fileLength; i++) {
				char d = buff[i];

				if (d == '#')
					addLineToData = false;

				if (d == 's')
					addLineToData = false;

				if (d == 'o')
					addLineToData = false;


				if (d == '\n' && addLineToData == false) {
					addLineToData = true;
					continue;
				}

				if (!addLineToData)
					continue;

				data.push_back(buff[i]);
			}

			delete[] buff;

			data.push_back('\n');
			data.push_back('#');
			data.push_back('\n');
		}
		void readGuiGeometryFiles();

	public:

		GuiGeometryReader(const char *guiGeometryFile, GuiGeometryParser &guiGeometryParser);
		~GuiGeometryReader() = default;

	};

};

