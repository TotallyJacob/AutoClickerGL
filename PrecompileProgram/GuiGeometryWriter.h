#pragma once
namespace gui {

	class GuiGeometryWriter
	{
	public:
		GuiGeometryWriter() = default;
		~GuiGeometryWriter() = default;

		void writeGeometry(std::vector<float>& geometry);
	};

};

