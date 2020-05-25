#include "AutoClickerGL.h"

AutoClickerGL::AutoClickerGL() {
	init();
	
	if (error == -1) {
		return;
	}

	loop();
	cleanUp();
}

void AutoClickerGL::init() {
	//GLFW
	if (!glfwInit()) {
		glfwTerminate();
		error = -1;
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4.6);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4.6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(1280, 720, "test", NULL, NULL);

	if (!window) {
		glfwTerminate();
		error = -1;
		return;
	}

	glfwMakeContextCurrent(window);
	glfwShowWindow(window);

	//GLEW
	int code = glewInit();
	if (code != GLEW_OK) {
		std::cout << glewGetErrorString(code) << std::endl;
		error = -1;
		return;
	}

	engine::file::YAMLFile file("Config.yml");
	std::cout << file.getFloat("app-name") << std::endl;
}
void AutoClickerGL::loop() {

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
void AutoClickerGL::cleanUp() {
	glfwTerminate();
}