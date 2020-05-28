#include<iostream>
#include<fstream>

//My imports
#include"GuiGeometryReader.h"

constexpr static const char* guiGeometryPath = "C:\\Users\\Jacob\\source\\repos\\AutoClickerGL\\AutoClickerGL\\GuiGeometry.hpp";

int main() {
	gui::GuiGeometryParser guiGeometryParser;
	gui::GuiGeometryReader guiGeometryReader(guiGeometryPath, guiGeometryParser);

	system("pause");

	return 0;
}