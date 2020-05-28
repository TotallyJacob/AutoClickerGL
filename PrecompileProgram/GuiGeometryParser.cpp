#include "GuiGeometryParser.h"

using namespace gui;

void GuiGeometryParser::parseGeometry(std::vector<char>& guiGeometry) {

	std::vector<std::string> newData;
	std::string line = "";

	for (auto c : guiGeometry) {
		if (c == '\n') {

			std::vector<std::string> splitByWhiteSpace(0);

			util::split(line, splitByWhiteSpace, ' ');

			//newData.assign();

			line.empty();
			line.clear();

			continue;
		}

		line.push_back(c);
	}

}