#include "YAMLFile.h"

using namespace engine::file;

YAMLFile::YAMLFile(const char* fileName) : 
	fileData(),
	stringNodes(),
	floatNodes() {

	readFile(fileName, fileData);
	parseData(fileData);

	delete[] fileData.dataPointer;

}

//Public

//Private
void YAMLFile::readFile(const char *fileName, yaml::FileData &fileData) {

	std::ifstream file(fileName, std::ios::binary);
	std::streambuf* raw_buffer = file.rdbuf();


	file.seekg(0, std::ios::end);
	fileData.fileLength = file.tellg();
	file.seekg(0, std::ios::beg);

	fileData.dataPointer = new char[fileData.fileLength];

	raw_buffer->sgetn(fileData.dataPointer, fileData.fileLength);

	file.close();
}
void YAMLFile::parseData(yaml::FileData &fileData) {
	std::string line = "";
	//char line[64];

	yaml::Node<std::string> placeHolderNode = {};
	bool ignoreLine = false;

	for (unsigned int index = 0; index < fileData.fileLength; index++) {
	
		if (fileData.dataPointer[index] == '#')
			ignoreLine = true;

		if (fileData.dataPointer[index] == '\n') {
			if (ignoreLine) {
				ignoreLine = false;
				continue;
			}

			placeHolderNode.value = line;

			yaml::ValueType type = getValueType(line);

			std::cout << line << std::endl;

			switch(type){
			
			case yaml::ValueType::NOTYPE:
				std::cout << "INVALID NODE: " << placeHolderNode.key << std::endl;
				return;

			case yaml::ValueType::STRING:
				stringNodes.push_back(placeHolderNode);
				return;

			case yaml::ValueType::FLOAT:
				yaml::Node<float> node = {};
				node.key = placeHolderNode.key;
				node.value = strtof(placeHolderNode.value.c_str(), 0);

				floatNodes.push_back(node);
				return;
			}

			line.clear();
			continue;
		}

		if (fileData.dataPointer[index] == ':') {
			placeHolderNode.key = line;
			line.clear();
			continue;
		}


		line.push_back(fileData.dataPointer[index]);
	}

	yaml::ValueType type = getValueType(line);

	switch (type) {

	case YAMLType::NOTYPE:
		std::cout << "INVALID NODE: " << placeHolderNode.key << std::endl;
		return;

	case YAMLType::STRING:
		stringNodes.push_back(placeHolderNode);
		return;

	case YAMLType::FLOAT:
		YAMLNode<float> node = {};
		node.key = placeHolderNode.key;
		node.value = strtof(placeHolderNode.value.c_str(), 0);

		floatNodes.push_back(node);
		return;
	}

	line.clear();

}

//PreProcess
void YAMLFile::preReadFile(const char *fileName) const {
	std::ifstream file(fileName, std::ios::binary);
	std::streambuf* raw_buffer = file.rdbuf();


	file.seekg(0, std::ios::end);
	unsigned int fileLength = file.tellg();
	file.seekg(0, std::ios::beg);

	char *dataPointer = new char[fileData.fileLength];

	raw_buffer->sgetn(fileData.dataPointer, fileData.fileLength);

	file.close();
}
void YAMLFile::preProcessFile(yaml::PreProcessdData& preProcessedData, char* data, unsigned int size) const {

	unsigned int line_size = 0;

	for (int i = 0; i < size; i++) {

		if (data[i] = '\n')
			line_size++;

	}

	preProcessedData.num_lines = line_size;

	delete[] data;
}