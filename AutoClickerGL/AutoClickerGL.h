
//My imports
#include"YAMLFile.h"

#pragma once

class AutoClickerGL
{
private:

	void init();
	void loop();
	void cleanUp();

public:

	AutoClickerGL();
	~AutoClickerGL() = default;

	int end();

};



