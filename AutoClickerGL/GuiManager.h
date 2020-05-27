//My imports
#include"GuiRenderer.h"

#pragma once

namespace engine::gui {

	class GuiManager
	{
	private:
		GuiRenderer* guiRenderer;
	public:
		GuiManager(GuiRenderer *guiRenderer);
		~GuiManager() = default;

	};

};

