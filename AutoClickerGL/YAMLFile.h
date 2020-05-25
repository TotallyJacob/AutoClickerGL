//Standard imports
#include<iostream>
#include<fstream>
#include<vector>

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

		template<typename T>
		struct YAMLNode {
			const char* key;
			T value;
		};

		YAMLFileData fileData;

		FILE_CONSTEXPR void readFile(const char *fileName, YAMLFileData &fileData);
		FILE_CONSTEXPR void parseData(YAMLFileData &fileData);

		static inline void getType(char* chars, unsigned int num_chars) {

		}

	public:

		YAMLFile(const char *fileName);
		~YAMLFile() = default;


		template<typename T>
		FILE_CONSTEXPR T get(const char* name) const {

		}

	};

};

