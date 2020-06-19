#include<iostream>
#include<fstream>

//My imports
#include"GuiGeometryReader.h"
#include"GuiGeometryWriter.h"
#include"GuiGeometryParser.h"

constexpr static const char* guiGeometryPath = "C:\\Users\\Jacob\\source\\repos\\AutoClickerGL\\AutoClickerGL\\GuiGeometry.hpp";
constexpr static const char* guiTextureGeometryPath = "C:\\Users\\Jacob\\source\\repos\\AutoClickerGL\\AutoClickerGL\\GuiTextureGeometry.hpp";

int main() {

	/*GUI*/

	//Reading
	gui::GuiGeometryReader guiGeometryReader(guiGeometryPath);
	guiGeometryReader.readGuiGeometryFiles();

	//Parsing
	gui::GuiGeometryParser guiGeometryParser;
	guiGeometryParser.parseGeometry(guiGeometryReader);

	//Writing
	gui::GuiGeometryWriter guiGeometryWriter;
	guiGeometryWriter.writeDefaultGeometry(guiGeometryParser, guiGeometryPath);
	guiGeometryWriter.writeTexGeometry(guiGeometryParser, guiTextureGeometryPath);

	/**/

	return 0;
}