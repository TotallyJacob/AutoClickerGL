#include<iostream>
#include<vector>

//My imports
#include"GuiUtil.hpp"

#pragma once

namespace gui {

	class GuiGeometryWriter
	{

	private:
		struct GeometryData;

		constexpr static const char* guiGeometryPath = "C:\\Users\\Jacob\\source\\repos\\AutoClickerGL\\AutoClickerGL\\GuiGeometry.hpp";

		inline void setGeometryInfoDataStruct(std::stringstream &ss) const noexcept {
			ss << "struct GeometryInfo {\n";
			ss << "    unsigned int num_verts;\n";
			ss << "    unsigned int floatsToStartOfGeometry;\n";
			ss << "    const char *geometryName;\n";
			ss << "};\n";
		}
		inline void setGeometryInfoDataSize(std::stringstream& ss, unsigned int size) const {
			ss << "constexpr unsigned int geometryInfoSize = ";
			ss << size;
			ss << ";\n";
		}
		inline void setGeometryInfoDataArray(std::stringstream& ss, std::vector<GeometryData>& geometryData) {
			ss << "GeometryInfo geometryInfo[geometryInfoSize] = {\n";
			for (int i = 0; i < geometryData.size(); i++) {

				GeometryData d = geometryData.at(i);

				ss << "GeometryInfo{";
				ss << d.num_verts;
				ss << ",";
				ss << d.floatsFromStartOfGeometry;
				ss << ",";
				ss << "\"";
				ss << d.geometryName;
				ss << "\"";
				ss << "}";

				if (i == geometryData.size() - 1) {
					ss << "\n";
					continue;
				}

				ss << ",\n";
			}
			ss << "};\n";
		}

		inline void setGeometryVertexDataSize(std::stringstream& ss, unsigned int size) const {
			ss << "constexpr unsigned int vertexDataSize = ";
			ss << size;
			ss << ";\n";
		}
		inline void setGeometryVertexArray(std::stringstream& ss, std::vector<float> &verts) {
			ss << "float vertData[vertexDataSize] {";
			for (int i = 0; i < verts.size(); i++) {
				ss << verts.at(i);

				if (i == verts.size() - 1)
					continue;

				ss << ",";
			}
			ss << "};\n";
		}
		inline void newLine(std::stringstream& ss) const noexcept {
			ss << "\n";
		}

	public:

		struct GeometryData {
			unsigned int num_verts = 0;
			unsigned int floatsFromStartOfGeometry = 0;
			std::string geometryName;
		};

		GuiGeometryWriter() = default;
		~GuiGeometryWriter() = default;

		void writeGeometry(std::vector<float>& geometry, std::vector<GeometryData>& geometryData);
	};

};

