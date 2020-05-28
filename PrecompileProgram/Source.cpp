#include<iostream>
#include<fstream>

//My imports
#include"GuiGeometryLoader.h"

constexpr static const char* guiGeometryPath = "C:\\Users\\Jacob\\source\\repos\\AutoClickerGL\\AutoClickerGL\\GuiGeometry.hpp";

int main() {

	gui::GuiGeometryLoader guiGeometryLoader(guiGeometryPath);

	system("pause");

	return 0;
}