#include "GuiGeometryLoader.h"

using namespace gui;

GuiGeometryLoader::GuiGeometryLoader(const char* guiGeometryFile) 
	: guiGeometryFile(guiGeometryFile) {

	std::vector<std::wstring> filePaths(0);
	getGuiGeometryFiles(filePaths);

	for (auto v : filePaths)
		std::cout << util::narrow(v) << std::endl;

	char* data;
	unsigned int length = 0;

	data = util::readData<const char*>(guiGeometryFile, length);

	delete[] data;

}


//Private
const void GuiGeometryLoader::getGuiGeometryFiles(std::vector<std::wstring> &filePaths) const {

	std::wstring guiIdentifier(util::widen(guiIdentifier));

	for (const auto& entry : std::filesystem::directory_iterator(path)) {
		std::wstring path = entry.path();

		if (path.find(guiIdentifier) != std::wstring::npos) {
			filePaths.push_back(entry.path());
		}

	}
}