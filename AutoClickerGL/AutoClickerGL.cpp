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

	guiGeometryManager.freeGeometry();

	engine::gui::GuiManager guiManager(&guiRenderer);
	guiManager.setGeometryDataIds(guiGeometryManager.getGeometryInfoDataSize());

#define HEIGHT 560
#define WIDTH 980


	engine::gui::GuiContainer container = {};
	container.update = true;
	container.onUpdate = [](void* m, int x, int y) -> void {
		engine::gui::GuiManager* manager = ((engine::gui::GuiManager*)m);

		bool hover = x <= 300 + WIDTH && x > 100 + WIDTH && y >= 720 - HEIGHT - 200 && y < 720 - HEIGHT;
		bool hover2 = x <= 100 + WIDTH && x > 0 + WIDTH && y >= 720 - HEIGHT - 200 && y < 720 - HEIGHT;
		float testColour = manager->elementColour(1, 0);
		float testColour2 = manager->elementColour(0, 0);


		if (testColour != 0.0f && hover) {
			manager->setColour(1, glm::vec4(1.0f, 0.f, 0.f, 1.0f));
		}

		if (testColour2 != 1.0f && hover2) {
			manager->setColour(0, glm::vec4(0.0f, 0.f, 1.f, 1.0f));
		}

		if (testColour == 1.0f && !hover) {
			manager->setColour(1, glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
		}

		if (testColour2 == 0.0f && !hover2) {
			manager->setColour(0, glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
		}
	};
	container.position = glm::vec3(WIDTH, HEIGHT, 0.f);
	container.scale = glm::vec3(0.f, 0.f, 0.f);

	//Container
	container.setGuiGeometryIds(guiGeometryManager.getGeometryInfoDataSize());
	container.addElement({
		(guiGeometryManager.getGeometryId("square.obj")),
		0.1f,
		glm::vec3(100.f, 100.f, -10.f),
		glm::vec3(100.f, 100.f, 1.0f),
		glm::vec4(0.1f, 0.1f, 0.1f, 1.0f)
		});
	container.addElement({
	(guiGeometryManager.getGeometryId("square.obj")),
	0.1f,
	glm::vec3(200.f, 100.f, -10.f),
	glm::vec3(100.f, 100.f, 1.0f),
	glm::vec4(0.1f, 0.1f, 0.1f, 1.0f)
		});

	//Gui manager setup
	guiManager.addGuiContainer(container);
	guiManager.setDrawIndexs();
	guiManager.setRendererData();
	//


	glm::mat4 orthoMatrix = glm::ortho(0.f, 1280.f, 0.f, 720.f, 0.1f, 100.f);

	//test
	double px = 0, py = 0;

	autoClicker::Tick tick = {};

	while (!glfwWindowShouldClose(window)) {
		double startTime = glfwGetTime();

		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		//Drawing

		guiRenderer.render(&orthoMatrix[0][0]);

		
		//
		glfwSwapBuffers(window);
		glfwPollEvents();

		double elapsedtime = glfwGetTime() - startTime;
		autoClicker::updateTickTimes(tick, elapsedtime);

		if (autoClicker::onSlowTickTime(tick.slowTickTime)) { }
		if (autoClicker::onMedTickTime(tick.medTickTime)) {
			double x = 0, y = 0;
			glfwGetCursorPos(window, &x, &y);
			if (px != x || py != y) {
				guiManager.updateContainers(x, y);
				px = x;
				py = y;
			}

			if (x <= 300 + WIDTH && x > 100 + WIDTH && y >= 720 - HEIGHT - 200 && y < 720 - HEIGHT) {
				if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
					glfwSetWindowShouldClose(window, 1);
			}
		}
		if (autoClicker::onFastTickTime(tick.fastTickTime)) { }

	}
}
void AutoClickerGL::cleanUp() {
	glfwTerminate();
}