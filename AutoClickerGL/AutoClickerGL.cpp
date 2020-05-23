#include "AutoClickerGL.h"

AutoClickerGL::AutoClickerGL() {
	init();
	loop();
	cleanUp();
}

void AutoClickerGL::init() {
	util::file::YAMLFile file("Config.yml");
}

void AutoClickerGL::loop() {

}

void AutoClickerGL::cleanUp() {

}

int AutoClickerGL::end() {
	return 0;
}