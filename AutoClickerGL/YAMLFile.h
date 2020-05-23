//Standard imports
#include<iostream>
#include<fstream>

#define FILE_CONSTEXPR

#pragma once

namespace util::file {

	class YAMLFile
	{
	private:

		struct YAMLFileData {
			unsigned int fileLength = 0;
			char* dataPointer;
		};

		YAMLFileData fileData;

		FILE_CONSTEXPR void readFile(const char *fileName, YAMLFileData &fileData);
		FILE_CONSTEXPR void parseData(YAMLFileData &fileData);

	public:

		YAMLFile(const char *fileName);
		~YAMLFile() = default;


		template<typename T>
		FILE_CONSTEXPR T get(const char* name) const {

		}
	};

};

