#include "shaders.h"

namespace borsuk {
namespace shaders {

	Shader::Shader(char const * path, GLenum type)
		: shader_handle_{ path }
		, shader_id_{ glCreateShader(type) }
	{
		if (!shader_handle_)
			throw std::runtime_error("Cannot open file: " + std::string(path));
		std::getline(shader_handle_, shader_code_, '\0');

		if (!shader_code_.size())
			throw std::runtime_error("Error: shader file size == 0");
	}

	Shader::~Shader()
	{
		if (!close_flag_)
			deleteShader();
	}

	void Shader::compileShader()
	{
		char const* shader{ shader_code_.c_str() };
		glShaderSource(shader_id_, 1, &shader, nullptr);
		glCompileShader(shader_id_);
		checkCompilationStatus();
		std::cout << shader << std::endl;
	}

	void Shader::checkCompilationStatus() const
	{
		int success;
		char info_log[512];
		glGetShaderiv(shader_id_, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader_id_, 512, nullptr, info_log);
			throw std::runtime_error(info_log);
		}
	}

	void Shader::deleteShader()
	{
		glGetShaderiv(shader_id_, GL_DELETE_STATUS, &close_flag_);
		if (!close_flag_)
			glDeleteShader(shader_id_);
	}

} // namespace shaders

namespace program {

	void Program::attachShaders() const
	{
		for (auto const& x : shaders_)
			glAttachShader(id_, x);
	}

	void Program::link() const
	{
		glLinkProgram(id_);
		checkLinkingStatus();
		
		if (glGetError() != GL_NO_ERROR)
			throw std::domain_error("ERROR::PROGRAM::BAD_SHADER_VALUE");
	}

	void Program::checkLinkingStatus() const
	{
		int success;
		char info_log[512];
		glGetProgramiv(id_, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(id_, 512, nullptr, info_log);
			std::cerr << "ERROR::PROGRAM::LINKING_FAILED; check shaders ids" << std::endl;
			throw std::domain_error(info_log); // for some reason info_log remains empty after error occurence
		}
	}



} // namespace program
} // namespace borsuk

