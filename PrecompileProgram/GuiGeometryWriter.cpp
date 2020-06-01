#include "GuiGeometryWriter.h"

using namespace gui;

// @TODO temp

void GuiGeometryWriter::writeGeometry(std::vector<float> &verts, std::vector<GeometryData>& geometryData) {
	std::stringstream ss;

	//GeometryInfo struct
	ss << "struct GeometryInfo {\n";
	ss << "unsigned int num_verts;\n";
	ss << "unsigned int floatsToStartOfGeometry;\n";
	ss << "};\n";

	//
	ss << "\n";
	//

	//Verts array size
	ss << "constexpr unsigned int vertexDataSize = ";
	ss << verts.size();
	ss << ";\n";

	//Verts array
	ss << "float vertData[vertexDataSize] {";
	for (int i = 0; i < verts.size(); i++) {
		ss << verts.at(i);

		if (i == verts.size() - 1)
			continue;

		ss << ",";
	}
	ss << "};\n";

	//
	ss << "\n";
	//

	//Geometry info array size
	ss << "constexpr unsigned int geometryInfoSize = ";
	ss << geometryData.size();
	ss << ";\n";
	ss << "GeometryInfo geometryInfo[geometryInfoSize] = {\n";
	for (int i = 0; i < geometryData.size(); i++) {

		GeometryData d = geometryData.at(i);

		ss << "GeometryInfo{";
		ss << d.num_verts;
		ss << ",";
		ss << d.floatsFromStartOfGeometry;
		ss << "}";

		if (i == geometryData.size() - 1) {
			ss << "\n";
			continue;
		}
		
		ss << ",\n";
	}
	ss << "};\n";

	std::string data = ss.str();

	data.size();
	
	util::writeData(guiGeometryPath, data.data(), data.size());
}