#include "Shader.h"

#include <fstream>
#include <istream>
#include <stdexcept>
#include <sstream>
#include <string>

namespace simple {

Shader::Shader() {}

Shader::~Shader() {
	if (mVShader != INVALID_VALUE) { glDeleteShader(mVShader);  }
	if (mGShader != INVALID_VALUE) { glDeleteShader(mGShader);  }
	if (mFShader != INVALID_VALUE) { glDeleteShader(mFShader);  }
	if (mProgram != INVALID_VALUE) { glDeleteProgram(mProgram); }
}

void Shader::active() {
	if (mProgram != INVALID_VALUE) {
		glUseProgram(mProgram);
	} else {
		throw std::runtime_error("Shader program doesn't work!");
	}
}

void Shader::compile() {
	mProgram = glCreateProgram();

	if (mVShader != INVALID_VALUE) { glAttachShader(mProgram, mVShader); }
	if (mGShader != INVALID_VALUE) { glAttachShader(mProgram, mGShader); }
	if (mFShader != INVALID_VALUE) { glAttachShader(mProgram, mFShader); }

	glLinkProgram(mProgram);

	checkProgram(GL_LINK_STATUS);
	checkProgram(GL_VALIDATE_STATUS);

	if (mVShader != INVALID_VALUE) { glDeleteShader(mVShader); mVShader = INVALID_VALUE; }
	if (mGShader != INVALID_VALUE) { glDeleteShader(mGShader); mGShader = INVALID_VALUE; }
	if (mFShader != INVALID_VALUE) { glDeleteShader(mFShader); mFShader = INVALID_VALUE; }
}

void Shader::compileShader(std::string const& path, GLenum type, GLuint& shader) {

	std::ifstream file(path);

	if (!file.is_open()) { throw std::runtime_error("Error reading shader file: " + path); }

	std::stringstream stream;
	stream << file.rdbuf();

	std::string code = stream.str();
	GLchar const* data = code.c_str();

	shader = glCreateShader(type);
	glShaderSource(shader, 1, &data, nullptr);
	glCompileShader(shader);

	checkShader(shader);
}

void Shader::checkShader(GLuint shader) {
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if (status == GL_TRUE) { return; }

	uint32_t logSize = 1024;
	GLchar infoLog[logSize];
	glGetShaderInfoLog(shader, logSize, nullptr, infoLog);

	throw std::runtime_error("Shader compiler error: " + std::string(infoLog));
}

void Shader::checkProgram(GLenum type) {
	GLint status;
	glGetProgramiv(mProgram, type, &status);

	if (status == GL_TRUE) { return; }

	uint32_t logSize = 1024;
	GLchar infoLog[logSize];
	glGetProgramInfoLog(mProgram, logSize, nullptr, infoLog);

	throw std::runtime_error("Shader program error: " + std::string(infoLog));
}

GLuint Shader::getUniform(std::string const& name) {
	GLuint location = glGetUniformLocation(mProgram, name.c_str());
	if (location == INVALID_VALUE) {
		throw std::runtime_error("Not found uniform location: " + name);
	}
	return location;
}

GLuint Shader::getAttribute(std::string const& name) {
	GLuint location = glGetAttribLocation(mProgram, name.c_str());
	if (location == INVALID_VALUE) {
		throw std::runtime_error("Not found attribute location: " + name);
	}
	return location;
}

} // namespace simple
