#include<iostream>
#include<string>
#include<filesystem>
#include<fstream>
#include<locale>
#include<sstream>

#pragma once

namespace gui::util {

	//wchar and char util
	static const std::wstring widen(std::string string) {
		using namespace std;

		std::wostringstream wideStringStream;
		const ctype<wchar_t>& ctfacet = use_facet<ctype<wchar_t>>(wideStringStream.getloc());
		for (size_t t = 0; t < string.size(); t++) {
			wideStringStream << ctfacet.widen(string[t]);
		}

		return wideStringStream.str();
	}
	static const std::string narrow(std::wstring string) {
		using namespace std;

		ostringstream stringStream;

		const ctype<wchar_t>& ctfacet = use_facet<ctype<wchar_t>>(stringStream.getloc());
		for (size_t t = 0; t < string.size(); t++)
			stringStream << ctfacet.narrow(string[t], 0);

		return stringStream.str();
	}

	//Reading and writing util
	template<typename T>
	[[nodiscard]] static char* readData(T filePath,unsigned int& length) {
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
	static void writeData(T filePath, char* data, unsigned int length) {
		auto myfile = std::fstream(filePath, std::ios::out | std::ios::binary);
		myfile.write(&data[0], sizeof(char) * length);
		myfile.close();
	}
	
}