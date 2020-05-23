#include<iostream>
#include<fstream>

#pragma once

namespace util {

	static inline void readFile(const char *fileName) {
	
		std::ifstream file(fileName, std::ios::binary);
		std::streambuf* raw_buffer = file.rdbuf();

		file.seekg(0, std::ios::end);
		unsigned int length = file.tellg();
		file.seekg(0, std::ios::beg);

		char* data = new char[length];

		raw_buffer->sgetn(data, length);

		file.close();

		delete[] data;
	}


}
