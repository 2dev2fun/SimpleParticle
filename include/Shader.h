#pragma once

#include <Math/Matrix2x2.h>
#include <Math/Matrix2x2/Function.h>
#include <Math/Matrix3x3.h>
#include <Math/Matrix3x3/Function.h>
#include <Math/Matrix4x4.h>
#include <Math/Matrix4x4/Function.h>
#include <Math/Vector2.h>
#include <Math/Vector2/Function.h>
#include <Math/Vector3.h>
#include <Math/Vector3/Function.h>
#include <Math/Vector4.h>
#include <Math/Vector4/Function.h>

#include <glad/glad.h>

#include <string>

namespace simple {

class Shader {
public:
	void active();
protected:
	Shader();
	~Shader();

	void attachVS(std::string const& path);
	void attachGS(std::string const& path);
	void attachFS(std::string const& path);

	void compile();

	GLuint getUniform(std::string const& name);
	GLuint getAttribute(std::string const& name);

	void setInt(GLuint location, int32_t v0);
	void setInt(GLuint location, int32_t v0, int32_t v1);
	void setInt(GLuint location, int32_t v0, int32_t v1, int32_t v2);
	void setInt(GLuint location, int32_t v0, int32_t v1, int32_t v2, int32_t v3);

	void setFloat(GLuint location, float v0);
	void setFloat(GLuint location, float v0, float v1);
	void setFloat(GLuint location, float v0, float v1, float v2);
	void setFloat(GLuint location, float v0, float v1, float v2, float v3);

	void setMat2(GLuint location, Mat2 const& value, uint32_t number = 1);
	void setMat3(GLuint location, Mat3 const& value, uint32_t number = 1);
	void setMat4(GLuint location, Mat4 const& value, uint32_t number = 1);

	void setVec2(GLuint location, Vec2 const& value, uint32_t number = 1);
	void setVec3(GLuint location, Vec3 const& value, uint32_t number = 1);
	void setVec4(GLuint location, Vec4 const& value, uint32_t number = 1);

	static const GLuint INVALID_VALUE = 0xFFFFFFFF;
private:
	void compileShader(std::string const& path, GLenum type, GLuint& shader);

	void checkShader(GLuint shader);
	void checkProgram(GLenum type);

	GLuint mProgram = INVALID_VALUE;
	GLuint mVShader = INVALID_VALUE;
	GLuint mGShader = INVALID_VALUE;
	GLuint mFShader = INVALID_VALUE;
};

inline void Shader::attachVS(std::string const& path) {
	compileShader(path, GL_VERTEX_SHADER, mVShader);
}

inline void Shader::attachGS(std::string const& path) {
	compileShader(path, GL_GEOMETRY_SHADER, mGShader);
}

inline void Shader::attachFS(std::string const& path) {
	compileShader(path, GL_FRAGMENT_SHADER, mFShader);
}

inline void Shader::setInt(GLuint location, int32_t v0) {
	glUniform1i(location, v0);
}

inline void Shader::setInt(GLuint location, int32_t v0, int32_t v1) {
	glUniform2i(location, v0, v1);
}

inline void Shader::setInt(GLuint location, int32_t v0, int32_t v1, int32_t v2) {
	glUniform3i(location, v0, v1, v2);
}

inline void Shader::setInt(GLuint location, int32_t v0, int32_t v1, int32_t v2, int32_t v3) {
	glUniform4i(location, v0, v1, v2, v3);
}

inline void Shader::setFloat(GLuint location, float v0) {
	glUniform1f(location, v0);
}

inline void Shader::setFloat(GLuint location, float v0, float v1) {
	glUniform2f(location, v0, v1);
}

inline void Shader::setFloat(GLuint location, float v0, float v1, float v2) {
	glUniform3f(location, v0, v1, v2);
}

inline void Shader::setFloat(GLuint location, float v0, float v1, float v2, float v3) {
	glUniform4f(location, v0, v1, v2, v3);
}

inline void Shader::setMat2(GLuint location, Mat2 const& value, uint32_t number) {
	glUniformMatrix2fv(location, number, GL_FALSE, math::getPointer(value));
}

inline void Shader::setMat3(GLuint location, Mat3 const& value, uint32_t number) {
	glUniformMatrix3fv(location, number, GL_FALSE, math::getPointer(value));
}

inline void Shader::setMat4(GLuint location, Mat4 const& value, uint32_t number) {
	glUniformMatrix4fv(location, number, GL_FALSE, math::getPointer(value));
}

inline void Shader::setVec2(GLuint location, Vec2 const& value, uint32_t number) {
	glUniform2fv(location, number, math::getPointer(value));
}

inline void Shader::setVec3(GLuint location, Vec3 const& value, uint32_t number) {
	glUniform3fv(location, number, math::getPointer(value));
}

inline void Shader::setVec4(GLuint location, Vec4 const& value, uint32_t number) {
	glUniform4fv(location, number, math::getPointer(value));
}

} // namespace engine
