#include "GuiGeometryManager.h"

using namespace engine::gui;

GuiGeometryManager::GuiGeometryManager() {
	setGeometry();
}

GuiGeometryManager::~GuiGeometryManager() {
	if(!geometryFreed)
		freeGeometry();
}


//private
void GuiGeometryManager::setGeometry() {
	//Data in here to go out of scope
	#include"GuiGeometry.hpp"
	
	//size
	this->vertexDataSize = vertexDataSize;
	this->geometryInfoDataSize = geometryInfoSize;

	//Arrays init
	this->vertexData = new float[vertexDataSize];
	this->geometryInfoData = new GeometryInfoData[geometryInfoSize];

	//Setting array data
	memcpy(this->vertexData, vertData, sizeof(*vertexData) * vertexDataSize);
	memcpy(this->geometryInfoData, geometryInfo, sizeof(*geometryInfoData) * geometryInfoSize);

	for (int i = 0; i < geometryInfoSize; i++) {
		GeometryInfoData geometryInfoData = this->geometryInfoData[i];
		geometryId.emplace(geometryInfoData.geometryName, i);
	}

}