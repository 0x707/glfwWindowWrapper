#include <iostream>

#include "window_class.h"
#include "shaders.h"

int main()
{
	try {
		borsuk::initGLFW();

		borsuk::Window window(800, 600, "Borsuk");
		borsuk::Shader vertex_shader("shaders\\vertex.txt", GL_VERTEX_SHADER);
		borsuk::Shader fragment_shader("shaders\\fragment.txt", GL_FRAGMENT_SHADER);

		vertex_shader.compileShader();
		fragment_shader.compileShader();

		unsigned shaderProgram{ glCreateProgram() };
		glAttachShader(shaderProgram, vertex_shader.getShader());
		glAttachShader(shaderProgram, fragment_shader.getShader());
		glLinkProgram(shaderProgram);

		int success;
		char info_log[512];
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderProgram, 512, nullptr, info_log);
			std::cerr << "PROGRAM::LINK::FAILED: " << info_log << std::endl;
		}

		vertex_shader.deleteShader();
		fragment_shader.deleteShader();

		float vertices[] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.3f, 0.2f, 0.1f
		};

		unsigned indices[] = {
			0, 1, 2,
			0, 2, 3
		};

		unsigned VAO, VBO, EBO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glUseProgram(shaderProgram);

		while (!window.windowClosed()) {
			glClear(GL_COLOR_BUFFER_BIT);
			//glDrawArrays(GL_TRIANGLES, 0, 3);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
			window.handleEvents();
		}
	}
	catch (std::runtime_error& e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}