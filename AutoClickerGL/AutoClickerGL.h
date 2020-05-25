#include<iostream>
#include<thread>

#define GLEW_STATIC

//dependencies
#include"GL/glew.h"
#include"GLFW/glfw3.h"

//My imports
#include"YAMLFile.h"

//My defines

#define TICK_RATE_FAST 0.001f
#define TICK_RATE_MED 0.1f
#define TICK_RATE_SLOW 1.f

#pragma once

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



