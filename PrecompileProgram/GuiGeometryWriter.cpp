#include "GuiGeometryWriter.h"

using namespace gui;

// @TODO temp

void GuiGeometryWriter::writeGeometry(std::vector<float> &verts, std::vector<GeometryData>& geometryData) {
	std::stringstream ss;

	//GeometryInfo struct
	setGeometryInfoDataStruct(ss);

	newLine(ss);

	//Vertex
	setGeometryVertexDataSize(ss, verts.size());
	setGeometryVertexArray(ss, verts);

	newLine(ss);

	//Geometry info array size
	setGeometryInfoDataSize(ss, geometryData.size());
	setGeometryInfoDataArray(ss, geometryData);

	std::string data = ss.str();

	util::writeData(guiGeometryPath, data.data(), data.size());
}