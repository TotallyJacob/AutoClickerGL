#pragma once

#include<iostream>
#include<string>
#include<filesystem>
#include<fstream>
#include<locale>
#include<sstream>

//My imports
#include"GuiUtil.hpp"

namespace gui {

	class GuiGeometryReader
	{
	private:

		const char* guiGeometryFile;

		std::vector<char> geometryFileData;
		std::vector<std::string> geometryFileNames;


		inline static void readGuiGeometryData(std::wstring filePath, std::vector<char>& data, char qualifier) {
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
			data.push_back(qualifier);
			data.push_back('\n');
		}

	public:

		GuiGeometryReader(const char *guiGeometryFile);
		~GuiGeometryReader() = default;

		void readGuiGeometryFiles();

		//Getters
		std::vector<char>& getGeometryFileData() {
			return geometryFileData;
		}

		std::vector<std::string>& getGeometryFileNames() {
			return geometryFileNames;
		}

	};

};

