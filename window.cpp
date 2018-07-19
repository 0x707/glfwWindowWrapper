#include <iostream>

#include "window_class.h"
#include "shaders.h"
#include "drawing.h"

int main()
{
	try {
		borsuk::initGLFW();

		borsuk::Window window(800, 600, "Borsuk");
		borsuk::shaders::Shader vertex_shader("shaders\\vertex.txt", GL_VERTEX_SHADER);
		borsuk::shaders::Shader fragment_shader("shaders\\fragment.txt", GL_FRAGMENT_SHADER);

		vertex_shader.compileShader();
		fragment_shader.compileShader();

		// Program ctor can take any type convertible to unsigned (even sidnged arithmetic types)
		borsuk::program::Program p{vertex_shader.getShader(), fragment_shader.getShader()};
		p.attachShaders();
		p.link(); // I can make ::link() function take delete its shader (in vector shaders_)
				  // but Im not sure if its a good idea

		vertex_shader.deleteShader();
		fragment_shader.deleteShader();
		
		borsuk::shapes::Square square{
			borsuk::Vertex2DCol{ -0.5f, -0.5f, 1.0f, 0.0f, 0.0f },
			borsuk::Vertex2DCol{ -0.5f, 0.5f, 0.0f, 1.0f, 0.0f },
			borsuk::Vertex2DCol{ 0.5f, 0.5f, 0.0f, 0.0f, 1.0f },
			borsuk::Vertex2DCol{ 0.5f, -0.5f, 0.3f, 0.2f, 0.1f }};

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
		glBufferData(GL_ARRAY_BUFFER, square.Vertices().size() * sizeof(float), square.Vertices().data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		p.use();

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
	catch (std::domain_error& e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}