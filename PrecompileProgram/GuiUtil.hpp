#include<iostream>
#include<string>
#include<filesystem>
#include<fstream>
#include<locale>
#include<sstream>

#pragma once

// @TODO manage all the inlines -> maybe source

namespace gui::util {

	//Misc
	inline constexpr unsigned int getGeometryIndexSize(unsigned int x) {
		return (x < 10 ? 1 :
			(x < 100 ? 2 :
				(x < 1000 ? 3 :
					(x < 10000 ? 4 :
						(x < 100000 ? 5 :
							(x < 1000000 ? 6 :
								(x < 10000000 ? 7 :
									(x < 100000000 ? 8 :
										(x < 1000000000 ? 9 :
											10))))))))) + 2; //+2 for \n and #
	}
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

	inline static void readGuiGeometryData(std::wstring filePath, std::vector<char> &data, unsigned int geometryIndex) {
		std::ifstream file(filePath, std::ios::binary);
		std::streambuf* raw_buffer = file.rdbuf();

		file.seekg(0, std::ios::end);
		unsigned int fileLength = file.tellg();
		file.seekg(0, std::ios::beg);

		const unsigned int geometryIndexSize = getGeometryIndexSize(geometryIndex);

		data.reserve(fileLength + geometryIndexSize);
		data.resize(fileLength + geometryIndexSize);

		raw_buffer->sgetn(&data[0], fileLength);

		file.close();

		// @TODO make better

		std::stringstream ss;

		ss << "#";
		ss << geometryIndex;
		ss << '\n';

		std::string string = ss.str();

		for (int i = string.size(); i > -1; i--)
			data.insert(data.begin(), string[i]);

	}
	
	template<typename T>
	inline static void writeData(T filePath, char* data, unsigned int length) {
		auto myfile = std::fstream(filePath, std::ios::out | std::ios::binary);
		myfile.write(&data[0], sizeof(char) * length);
		myfile.close();
	}
	
}