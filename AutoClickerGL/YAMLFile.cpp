#include "YAMLFile.h"

using namespace util::file;

YAMLFile::YAMLFile(const char* fileName) : fileData() {
	readFile(fileName, fileData);
	parseData(fileData);

	delete[] fileData.dataPointer;
}

//Public

//Private
void YAMLFile::readFile(const char *fileName, YAMLFileData &fileData) {

	std::ifstream file(fileName, std::ios::binary);
	std::streambuf* raw_buffer = file.rdbuf();


	file.seekg(0, std::ios::end);
	fileData.fileLength = file.tellg();
	file.seekg(0, std::ios::beg);

	std::cout << fileData.fileLength << std::endl;

	fileData.dataPointer = new char[fileData.fileLength];

	raw_buffer->sgetn(fileData.dataPointer, fileData.fileLength);

	file.close();
}
void YAMLFile::parseData(YAMLFileData &fileData) {

	for (int index = 0; index < fileData.fileLength; index++) {
	
		std::cout << fileData.dataPointer[index];
	
	}

	std::cout << "end" << std::endl;

}