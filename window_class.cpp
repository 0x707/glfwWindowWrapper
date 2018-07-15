#include "window_class.h"
#include <stdio.h>

namespace borsuk {

	Window::Window(int width, int height, char const * name)
		: window_{ glfwCreateWindow(width, height, name, nullptr, nullptr) }
	{
		if (window_ == nullptr)
			throw (std::runtime_error("Failed to initialize window"));
		glfwMakeContextCurrent(window_);
		glfwSetFramebufferSizeCallback(window_, framebufferSizeCallback);
	}

	void Window::renderLoop()
	{
		while (!glfwWindowShouldClose(window_)) {

			glClear(GL_COLOR_BUFFER_BIT);

			processInput(window_);
			glfwSwapBuffers(window_);
			glfwPollEvents();
		}
	}

	void initGLFW()
	{
		glfwInit();
		glfwSetErrorCallback(errorCallback);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}

	void errorCallback(int error, char const * description)
	{
		puts(description);
	}

	void checkGLADinit()
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			throw std::runtime_error("Failed to initialize GLAD");
	}

	void processInput(GLFWwindow *window)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
	}

	void framebufferSizeCallback(GLFWwindow *window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}


} // namespace Borsuk
