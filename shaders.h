#pragma once
#include <fstream>
#include <string>
#include <iostream>

namespace borsuk
{
	struct Shader
	{
		Shader(char const* path, GLenum type)
			: shader_handle_{ path }
			, shader_id_{glCreateShader(type)}
		{
			if (!shader_handle_)
				throw std::runtime_error("Cannot open file: " + std::string(path));
			std::getline(shader_handle_, shader_code_, '\0');

			if (!shader_code_.size())
				throw std::runtime_error("Error: shader file size == 0");
		}

		~Shader()
		{
			int delete_flag;
			glGetShaderiv(shader_id_, GL_DELETE_STATUS, &delete_flag);
			if (!delete_flag)
				glDeleteShader(shader_id_);

		}

		void compileShader()
		{
			char const* shader{ shader_code_.c_str() };
			glShaderSource(shader_id_, 1, &shader, nullptr);
			glCompileShader(shader_id_);
			checkCompilationStatus();
			std::cout << shader << std::endl;
		}

		void checkCompilationStatus() const
		{
			int success;
			char info_log[512];
			glGetShaderiv(shader_id_, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(shader_id_, 512, nullptr, info_log);
				throw std::runtime_error(info_log);
			}
		}

		void deleteShader()
		{
			glDeleteShader(shader_id_);
		}

		unsigned getShader() const { return shader_id_; }
	
	private:
		std::ifstream shader_handle_;
		std::string shader_code_;
		unsigned shader_id_;
	};

} // namespace borsuk