#pragma once

#include<iostream>
#include<vector>

//My imports
#include"GuiUtil.hpp"
#include"GuiGeometryParser.h"

namespace gui {

	class GuiGeometryWriter
	{

	private:

		inline void setGeometryInfoDataStruct(std::stringstream &ss, const char * specialQualifier) const noexcept {
			ss << "struct ";
			ss << specialQualifier;
			ss<< "GeometryInfo {\n";
			ss << "    unsigned int num_verts;\n";
			ss << "    unsigned int floatsToStartOfGeometry;\n";
			ss << "    const char *geometryName;\n";
			ss << "};\n";
		}
		inline void setGeometryInfoDataSize(std::stringstream& ss, unsigned int size, const char* specialQualifier) const {
			ss << "constexpr unsigned int ";
			ss << specialQualifier;
			ss << "geometryInfoSize = ";
			ss << size;
			ss << ";\n";
		}
		inline void setGeometryInfoDataArray(std::stringstream& ss, std::vector<util::GeometryData>& geometryData, const char* specialQualifier) {
			ss << "GeometryInfo ";
			ss << specialQualifier;
			ss << "geometryInfo[";
			ss << specialQualifier;
			ss<< "geometryInfoSize] = { \n";
			for (int i = 0; i < geometryData.size(); i++) {

				util::GeometryData d = geometryData.at(i);

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

		inline void setGeometryVertexDataSize(std::stringstream& ss, unsigned int size, const char* specialQualifier) const {
			ss << "constexpr unsigned int ";
			ss << specialQualifier;
			ss<< "vertexDataSize = ";
			ss << size;
			ss << ";\n";
		}
		inline void setGeometryVertexArray(std::stringstream& ss, std::vector<float> &verts, const char* specialQualifier) {
			ss << "float ";
			ss << specialQualifier;
			ss << "vertData[";
			ss << specialQualifier;
			ss << "vertexDataSize]{ ";
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

		void writeGeometry(std::vector<float>& verts, std::vector<util::GeometryData>& geometryData, const char* guiGeometryPath, const char* guiSpecialQualifier);

	public:

		GuiGeometryWriter() = default;
		~GuiGeometryWriter() = default;

		void writeTexGeometry(GuiGeometryParser& guiGeometryParser, const char* guiTexGeometryPath);
		void writeDefaultGeometry(GuiGeometryParser& guiGeometryParser, const char* guiGeometryPath);
	};

};

