#pragma once

#include<iostream>
#include<string>
#include<filesystem>
#include<fstream>
#include<locale>
#include<sstream>

// @TODO manage all the inlines -> maybe source

namespace gui::util {

	struct GeometryData {
		unsigned int num_verts = 0;
		unsigned int floatsFromStartOfGeometry = 0;
		std::string geometryName;
	};

	struct GuiGeometry {
		std::vector<float> verts = std::vector<float>(0);
		std::vector<GeometryData> geometryData = std::vector<GeometryData>(0);
	};


	//Data
	constexpr static char guiTexQualifier = 't';
	constexpr static const char* guiTexSpecialQualifier = "Tex";
	constexpr static const char* guiTexIdentifier = "guiTexGeo.";
	constexpr static unsigned int guiTexIdentifierLength = 10;

	constexpr static char guiQualifier = 'n';
	constexpr static const char* guiSpecialQualifier = "";
	constexpr static const char* guiIdentifier = "guiGeo.";
	constexpr static unsigned int guiIdentifierLength = 7;

	constexpr static const char* path = "C:\\Users\\Jacob\\source\\repos\\AutoClickerGL\\AutoClickerGL";

	//Misc
	inline size_t split(const std::string& txt, std::vector<std::string>& strs, char ch)
	{
		size_t pos = txt.find(ch);
		size_t initialPos = 0;
		strs.clear();

		// Decompose statement
		while (pos != std::string::npos) {
			strs.push_back(txt.substr(initialPos, pos - initialPos));
			initialPos = pos + 1;

			pos = txt.find(ch, initialPos);
		}

		// Add the last one
		strs.push_back(txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1));

		return strs.size();
	}
	inline void toSplitWhitespace(std::vector<char>& currentData, std::vector<std::vector<std::string>>& newData) {
		std::string line = "";

		using SplitLine = std::vector<std::string>;

		for (auto c : currentData) {
			if (c == '\n') {

				SplitLine splitByWhiteSpace(0);
				split(line, splitByWhiteSpace, ' ');

				newData.push_back(std::move(splitByWhiteSpace));

				line.empty();
				line.clear();

				continue;
			}

			line.push_back(c);
		}
	}

	//wchar and char util
	inline static const std::wstring widen(std::string string) {
		using namespace std;

		std::wostringstream wideStringStream;
		const ctype<wchar_t>& ctfacet = use_facet<ctype<wchar_t>>(wideStringStream.getloc());
		for (size_t t = 0; t < string.size(); t++) {
			wideStringStream << ctfacet.widen(string[t]);
		}

		return wideStringStream.str();
	}
	inline static const std::string narrow(std::wstring string) {
		using namespace std;

		ostringstream stringStream;

		const ctype<wchar_t>& ctfacet = use_facet<ctype<wchar_t>>(stringStream.getloc());
		for (size_t t = 0; t < string.size(); t++)
			stringStream << ctfacet.narrow(string[t], 0);

		return stringStream.str();
	}

	//Reading and writing util
	template<typename T>
	[[nodiscard]] inline static char* readData(T filePath,unsigned int& length) {
		std::ifstream file(filePath, std::ios::binary);
		std::streambuf* raw_buffer = file.rdbuf();

		file.seekg(0, std::ios::end);
		length = file.tellg();
		file.seekg(0, std::ios::beg);

		char* data = new char[length];

		raw_buffer->sgetn(data, length);

		file.close();

		return data;
	}
	
	template<typename T>
	inline static void writeData(T filePath, char* data, unsigned int length) {
		auto myfile = std::fstream(filePath, std::ios::out | std::ios::binary);
		myfile.write(&data[0], sizeof(char) * length);
		myfile.close();
	}
	
}