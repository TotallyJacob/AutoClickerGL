#include<iostream>

#define GLEW_STATIC

//dependencies
#include"GL/glew.h"
#include"GLFW/glfw3.h"
#include"GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"
#include "GLM/gtx/transform.hpp"

//My imports
#include"YAMLFile.h"
#include"GuiRenderer.h"
#include"GuiGeometryManager.h"
#include"GuiManager.h"

//My defines
#define TICK_RATE_FAST 0.001f
#define TICK_RATE_MED 0.02f
#define TICK_RATE_SLOW 1.f

#pragma once

namespace autoClicker {

	struct Tick {
		double slowTickTime = 0, medTickTime = 0, fastTickTime = 0;
	};

	static void updateTickTimes(Tick& tick, double elapsed) {
		tick.slowTickTime += elapsed;
		tick.medTickTime += elapsed;
		tick.fastTickTime += elapsed;
	}

	static bool onSlowTickTime(double &slowTickTime) {
		if (slowTickTime >= TICK_RATE_SLOW) {
			slowTickTime = 0;

			return true;
		}

		return false;
	}
	static bool onMedTickTime(double &medTickTime) {
		if (medTickTime >= TICK_RATE_MED) {
			medTickTime = 0;

			return true;
		}

		return false;
	}
	static bool onFastTickTime(double &fastTickTime) {
		if (fastTickTime == TICK_RATE_FAST) {
			fastTickTime = 0;

			return true;
		}

		return false;
	}
}

class AutoClickerGL
{
private:

	//Data
	GLFWwindow* window;

	unsigned int error = 0;

	void init();
	void loop();
	void cleanUp();

public:

	AutoClickerGL();
	~AutoClickerGL() = default;

	inline const int end() const {
		return error;
	}

};



