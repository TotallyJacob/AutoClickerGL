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

	fileData.dataPointer = new char[fileData.fileLength];

	raw_buffer->sgetn(fileData.dataPointer, fileData.fileLength);

	file.close();
}

/*

@TODO un-hard coded line restriction size

*/
void YAMLFile::parseData(YAMLFileData &fileData) {
	std::string line = "";
	//char line[64];

	for (unsigned int index = 0; index < fileData.fileLength; index++) {
		
		if (fileData.dataPointer[index] == '\n') {
			line.clear();
			continue;
		}

		if (fileData.dataPointer[index] == ':') {
			std::cout << line << std::endl;
		}


		line.push_back(fileData.dataPointer[index]);
	}

	line.clear();

}