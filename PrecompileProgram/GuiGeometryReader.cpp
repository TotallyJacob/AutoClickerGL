#include "GuiGeometryReader.h"

using namespace gui;

GuiGeometryReader::GuiGeometryReader(const char* guiGeometryFile, GuiGeometryParser &guiGeometryParser) 
	: guiGeometryFile(guiGeometryFile) {

	readGuiGeometryFiles();

	guiGeometryParser.parseGeometry(geometryFileData, geometryFileNames);
}

//Private
void GuiGeometryReader::readGuiGeometryFiles() {
	
	std::wstring guiIdentifier(util::widen(guiIdentifier));

	unsigned int guiGeometryIndex = 0;

	for (const auto& entry : std::filesystem::directory_iterator(path)) {

		std::wstring path = entry.path();

		//If the path has guiIdentifier in it
		size_t pathFind = path.find(guiIdentifier);
		if (pathFind != std::wstring::npos) {

			geometryFileNames.push_back(util::narrow(path.substr(pathFind + guiIdentifierLength, path.size())));

			readGuiGeometryData(path, geometryFileData, guiGeometryIndex);

			guiGeometryIndex++;
		}
		
	}
}