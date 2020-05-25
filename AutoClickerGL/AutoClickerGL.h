//dependencies
#include"GL/glew.h"
#include"GLFW/glfw3.h"

//My imports
#include"YAMLFile.h"

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

	int end();

};



