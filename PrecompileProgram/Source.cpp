#include<iostream>
#include<fstream>

//My imports
#include"GuiGeometryParser.h"
#include"GuiGeometryReader.h"
#include"GuiGeometryWriter.h"

constexpr static const char* guiGeometryPath = "C:\\Users\\Jacob\\source\\repos\\AutoClickerGL\\AutoClickerGL\\GuiGeometry.hpp";

int main() {

	//Gui
	gui::GuiGeometryWriter guiGeometryWriter;
	gui::GuiGeometryParser guiGeometryParser(&guiGeometryWriter);
	gui::GuiGeometryReader guiGeometryReader(guiGeometryPath, guiGeometryParser);

	system("pause");

	return 0;
}