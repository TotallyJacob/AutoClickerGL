#include "GuiGeometryParser.h"

using namespace gui;

GuiGeometryParser::GuiGeometryParser() {

	this->defaultGeometry = {};
	this->textureGeometry = {};

}

// @TODO make better

void GuiGeometryParser::parse(std::vector<SplitLine>& splitLine, std::vector<std::string> &geometryFileNames) {
	std::vector<float>* verts = &defaultGeometry.verts;
	std::vector<util::GeometryData>* geometryData = &defaultGeometry.geometryData;

	//Temp data for parsing
	std::vector<float> temp_uv(0);
	std::vector<float> temp_vertices(0);
	bool parseTextureCoords = false;
	
	//Verts
	unsigned int current_normal_verts = 0, current_texture_verts = 0;
	//Geometry
	unsigned int current_normal_geometry = 0, current_texture_geometry = 0;
	//Parsing
	unsigned int vertexIndex = 0, texCoordIndex = 0;

	for (SplitLine line : splitLine) {

		if (line.at(0)[0] == '#') {


			if (parseTextureCoords) {
				geometryData->push_back({ current_texture_geometry, current_texture_verts, geometryFileNames.at(current_texture_geometry + current_normal_geometry) });
				current_texture_geometry++;
			}
			else {
				geometryData->push_back({ current_normal_geometry, current_normal_verts, geometryFileNames.at(current_texture_geometry + current_normal_geometry) });
				current_normal_geometry++;
			}

			//resetting data
			verts = &defaultGeometry.verts;
			geometryData = &defaultGeometry.geometryData;
			temp_uv.resize(0);
			temp_vertices.resize(0);
			parseTextureCoords = false;

		}
		if (line.at(0) == "v") {

			temp_vertices.push_back(atof(line.at(1).c_str()));
			temp_vertices.push_back(atof(line.at(2).c_str()));
			temp_vertices.push_back(atof(line.at(3).c_str()));
			continue;
		}
		if (line.at(0) == "vt") {

			if (!parseTextureCoords) {
				parseTextureCoords = true;

				verts = &textureGeometry.verts;
				geometryData = &textureGeometry.geometryData;
			}

			temp_uv.push_back(atof(line.at(1).c_str()));
			temp_uv.push_back(atof(line.at(2).c_str()));
			continue;
		}
		if (line.at(0) == "f") {

			for (int i = 1; i < 4; i++) {

				//Parsing
				std::stringstream ss;
				ss << line.at(i);

				//Vertex
				ss >> vertexIndex;
				vertexIndex--; //So 1 = 0 (converts to array index)
				vertexIndex *= 3; //Because 1 responds to 3 vertices, 3 floats

				verts->push_back(temp_vertices.at(vertexIndex));
				verts->push_back(temp_vertices.at(vertexIndex + 1));
				verts->push_back(temp_vertices.at(vertexIndex + 2));

				//Tex coord
				if (parseTextureCoords) {

					ss >> texCoordIndex;
					texCoordIndex--;//Converts to array index format
					texCoordIndex *= 2;//because 1 responds to 2 uvs

					verts->push_back(temp_uv.at(texCoordIndex));
					verts->push_back(temp_uv.at(texCoordIndex + 1));

					current_texture_verts += (2 + 3);
					continue;
				}

				current_normal_verts += 3;
			}

		}

	}
}
void GuiGeometryParser::parseGeometry(GuiGeometryReader& guiGeometryReader) {

	//Getting data
	std::vector<char>& guiGeometry = guiGeometryReader.getGeometryFileData();
	std::vector<std::string>& geometryFileNames = guiGeometryReader.getGeometryFileNames();

	//Spliting data
	using SplitLine = std::vector<std::string>;
	std::vector<SplitLine> newData;
	util::toSplitWhitespace(guiGeometry, newData);

	parse(newData, geometryFileNames);
}