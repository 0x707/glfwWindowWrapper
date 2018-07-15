#include <iostream>

#include "window_class.h"

int main()
{
	try {
		borsuk::initGLFW();

		borsuk::Window window(800, 600, "Borsuk");
		borsuk::checkGLADinit();

		window.renderLoop();
	}
	catch (std::runtime_error& e) {
		std::cerr << e.what() << std::endl;
	}

	glfwTerminate();
	return 0;
}