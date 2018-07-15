#pragma once
#include <stdexcept>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

namespace borsuk
{
	void framebufferSizeCallback(GLFWwindow *, int, int);
	class Window
	{
	public:
		Window(int, int, char const * = "");
		~Window() { glfwTerminate(); }

		void handleEvents() const;
		bool windowClosed() const { return glfwWindowShouldClose(window_); };

	private:
		GLFWwindow * window_;
	};

	void initGLFW();
	void errorCallback(int, char const *);
	void checkGLADinit();
	void processInput(GLFWwindow *);

}