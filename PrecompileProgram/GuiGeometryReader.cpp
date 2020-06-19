#include "GuiGeometryReader.h"

using namespace gui;

GuiGeometryReader::GuiGeometryReader(const char* guiGeometryFile) 
	: guiGeometryFile(guiGeometryFile) {
}

//Private
void GuiGeometryReader::readGuiGeometryFiles() {
	
	std::wstring guiIdentifier(util::widen(util::guiIdentifier));
	std::wstring guiTexIdentifier(util::widen(util::guiTexIdentifier));

	for (const auto& entry : std::filesystem::directory_iterator(util::path)) {

		std::wstring path = entry.path();

		//Handle normal geometry
		size_t pathFind = path.find(guiIdentifier);
		if (pathFind != std::wstring::npos) {

			geometryFileNames.push_back(util::narrow(path.substr(pathFind + util::guiIdentifierLength, path.size())));

			readGuiGeometryData(path, geometryFileData, util::guiQualifier);

			continue;
		}

		//Handle texture geometry
		pathFind = path.find(guiTexIdentifier);
		if (pathFind != std::wstring::npos) {

			geometryFileNames.push_back(util::narrow(path.substr(pathFind + util::guiTexIdentifierLength, path.size())));

			readGuiGeometryData(path, geometryFileData, util::guiTexQualifier);

			continue;
		}
		
	}
}