#pragma once
#include "glad/glad.h"
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

namespace borsuk {
namespace shaders {

	class Shader
	{
	public:
		Shader(char const*, GLenum);
		~Shader();

		void compileShader();
		void checkCompilationStatus() const;
		void deleteShader();
		unsigned getShader() const { return shader_id_; }

		// I delete it just for now, to ensure rule of 5
		Shader(const Shader&) = delete;
		Shader(Shader&&) = delete;
		Shader& operator=(const Shader&) = delete;
		Shader& operator=(Shader&&) = delete;
	private:
		std::ifstream shader_handle_;
		std::string shader_code_;
		unsigned shader_id_;
		int close_flag_ = 0;
	};

} // namespace shaders

namespace program {

	class Program
	{
	public:
		template<typename... Shaders>
		explicit Program(Shaders... shaders)
			: id_{ glCreateProgram() }
		{
			//(shaders_.emplace_back(shaders), ...); // c++ 17
			int a[] = { 0, (shaders_.push_back(shaders), 0)... }; // c++ <= 14
			static_cast<void>(a);
		}

		void attachShaders() const;
		void use() const { glUseProgram(id_); }
		void link() const;
		void checkLinkingStatus() const;

	private:
		unsigned id_;
		std::vector<GLuint> shaders_;
	};

} // nemespace program
} // namespace borsuk