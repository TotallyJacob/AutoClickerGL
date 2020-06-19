#include "GuiGeometryWriter.h"

using namespace gui;


// @TODO temp

void GuiGeometryWriter::writeGeometry(std::vector<float>& verts, std::vector<util::GeometryData>& geometryData, const char* guiGeometryPath, const char* guiSpecialQualifier) {
	std::stringstream guiSS;

	//GeometryInfo struct
	setGeometryInfoDataStruct(guiSS, guiSpecialQualifier);

	newLine(guiSS);

	//Vertex
	setGeometryVertexDataSize(guiSS, verts.size(), guiSpecialQualifier);
	setGeometryVertexArray(guiSS, verts, guiSpecialQualifier);

	newLine(guiSS);

	//Geometry info array size
	setGeometryInfoDataSize(guiSS, geometryData.size(), guiSpecialQualifier);
	setGeometryInfoDataArray(guiSS, geometryData, guiSpecialQualifier);

	std::string guiData = guiSS.str();
	util::writeData(guiGeometryPath, guiData.data(), guiData.size());
}

void GuiGeometryWriter::writeTexGeometry(GuiGeometryParser& guiGeometryParser, const char* guiTexGeometryPath) {
	std::vector<float>& verts = guiGeometryParser.getTextureVertices();
	std::vector<util::GeometryData>& geometryData = guiGeometryParser.getTextureGeometryData();

	if (verts.size() == 0 || geometryData.size() == 0) {

		std::cout << "No Textured geometry" << std::endl;
		return;
	}

	writeGeometry(verts, geometryData, guiTexGeometryPath, util::guiTexSpecialQualifier);
}

void GuiGeometryWriter::writeDefaultGeometry(GuiGeometryParser& guiGeometryParser, const char* guiGeometryPath) {
	std::vector<float>& verts = guiGeometryParser.getDefaultVertices();
	std::vector<util::GeometryData>& geometryData = guiGeometryParser.getDefaultGeometryData();

	if (verts.size() == 0 || geometryData.size() == 0) {

		std::cout << "No geometry" << std::endl;
		return;
	}
	writeGeometry(verts, geometryData, guiGeometryPath, util::guiSpecialQualifier);
}