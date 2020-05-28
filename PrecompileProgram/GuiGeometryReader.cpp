#include "GuiGeometryReader.h"

using namespace gui;

GuiGeometryReader::GuiGeometryReader(const char* guiGeometryFile, GuiGeometryParser &guiGeometryParser) 
	: guiGeometryFile(guiGeometryFile) {

	readGuiGeometryFiles();

	guiGeometryParser.parseGeometry(geometryFileData);
}

//Private
void GuiGeometryReader::readGuiGeometryFiles() {
	
	std::wstring guiIdentifier(util::widen(guiIdentifier));

	unsigned int guiGeometryIndex = 0;

	for (const auto& entry : std::filesystem::directory_iterator(path)) {

		std::wstring path = entry.path();

		//If the path has guiIdentifier in it
		if (path.find(guiIdentifier) != std::wstring::npos) {

			util::readGuiGeometryData(path, geometryFileData, guiGeometryIndex);

			guiGeometryIndex++;
		}
		
	}
}