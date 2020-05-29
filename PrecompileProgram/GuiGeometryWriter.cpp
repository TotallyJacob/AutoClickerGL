#include "GuiGeometryWriter.h"

using namespace gui;

// @TODO temp

void GuiGeometryWriter::writeGeometry(std::vector<float> &verts) {
	std::stringstream ss;

	ss << "constexpr unsigned int vertexDataSize = ";
	ss << verts.size();
	ss << ";\n";
	ss << "\n";
	ss << "float vertData[vertexDataSize] {";

	for (int i = 0; i < verts.size(); i++) {
		ss << verts.at(i);

		if (i == verts.size() - 1)
			continue;

		ss << ",";
	}

	ss << "};";

	std::string data = ss.str();

	data.size();
	
	util::writeData(guiGeometryPath, data.data(), data.size());
}