#include "AutoClickerGL.h"

AutoClickerGL::AutoClickerGL() {
	init();
	
	if (error == -1) {
		return;
	}

	loop();
	cleanUp();
}

void AutoClickerGL::init(){
	
	char c[3];
	std::cin >> c;

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

	// @TODO fix 
	//engine::file::YAMLFile file("Config.yml");
	//std::cout << file.getFloat("app-name") << std::endl;
}
void AutoClickerGL::loop() {

	//Gui
	engine::gui::GuiGeometryManager guiGeometryManager;
	engine::gui::GuiRenderer guiRenderer(&guiGeometryManager);
	engine::gui::GuiManager guiManager(&guiRenderer);

	glm::mat4 orthoMatrix = glm::ortho(0.f, 1280.f, 0.f, 720.f, 0.1f, 100.f);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		//Drawing

		guiRenderer.render(&orthoMatrix[0][0]);

		//
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
void AutoClickerGL::cleanUp() {
	glfwTerminate();
}