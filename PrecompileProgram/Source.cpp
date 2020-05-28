#include<iostream>
#include<fstream>

char* readGuiGeometry(unsigned int &fileLength) {
	const char* fileName = "C:\\Users\\Jacob\\source\\repos\\AutoClickerGL\\AutoClickerGL\\GuiGeometry.hpp";

	std::ifstream file(fileName, std::ios::binary);
	std::streambuf* raw_buffer = file.rdbuf();

	file.seekg(0, std::ios::end);
	fileLength = file.tellg();
	file.seekg(0, std::ios::beg);

	char* data = new char[fileLength];

	raw_buffer->sgetn(data, fileLength);

	file.close();

	return data;
}

void writeData(char* data, unsigned int dataLength) {
	const char* fileName = "C:\\Users\\Jacob\\source\\repos\\AutoClickerGL\\AutoClickerGL\\GuiGeometry.hpp";
	auto myfile = std::fstream(fileName, std::ios::out | std::ios::binary);
	myfile.write(&data[0], sizeof(char) * dataLength);
	myfile.close();
}

int main() {
	char* data;
	unsigned int fileLength = 0;

	data = readGuiGeometry(fileLength);

	for (int i = 0; i < fileLength; i++) {
		if (data[i] == '1') {
			data[i] = '1';
		}
	}

	writeData(data, fileLength);

	delete[] data;

	return 0;
}