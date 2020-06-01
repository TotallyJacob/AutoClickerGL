#include "GuiGeometryParser.h"

using namespace gui;

GuiGeometryParser::GuiGeometryParser(GuiGeometryWriter* guiGeometryWriter) {

	this->guiGeometryWriter = guiGeometryWriter;

}

// @TODO make better

void GuiGeometryParser::parseGeometry(std::vector<char>& guiGeometry) {

	using SplitLine = std::vector<std::string>;

	std::vector<SplitLine> newData;
	std::string line = "";

	for (auto c : guiGeometry) {
		if (c == '\n') {

			SplitLine splitByWhiteSpace(0);
			util::split(line, splitByWhiteSpace, ' ');

			newData.push_back(std::move(splitByWhiteSpace));

			line.empty();
			line.clear();

			continue;
		}

		line.push_back(c);
	}

	std::vector<float> temp_vertices(0);
	std::vector<float> verts(0);

	std::vector<GuiGeometryWriter::GeometryData> geometryData(0);
	unsigned int current_verts = 0;
	unsigned int current_geometry = 0;

	for (SplitLine line : newData) {

		if (line.at(0) == "#") {
			geometryData.push_back({ current_geometry, current_verts });
			current_geometry++;
			continue;
		}

		if (line.at(0) == "v") {

			temp_vertices.push_back(atof(line.at(1).c_str()));
			temp_vertices.push_back(atof(line.at(2).c_str()));
			temp_vertices.push_back(atof(line.at(3).c_str()));
			continue;
		}

		if (line.at(0) == "f") {

			for (int i = 1; i < 4; i++) {

				current_verts+= 3;

				std::stringstream ss;
				ss << line.at(i);

				unsigned int vertexIndex = 0;
				ss >> vertexIndex;

				vertexIndex--;
				vertexIndex *= 3;

				verts.push_back(temp_vertices.at(vertexIndex));
				verts.push_back(temp_vertices.at(vertexIndex + 1));
				verts.push_back(temp_vertices.at(vertexIndex + 2));
			}

		}

	}

	guiGeometryWriter->writeGeometry(verts, geometryData);
}