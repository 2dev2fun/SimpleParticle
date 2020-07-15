#pragma once

#include <Math/Vector2.h>
#include <Math/Vector4.h>

#include <glad/glad.h>

#include <cstddef>

namespace simple {

class ParticleVertexArray {
public:
	ParticleVertexArray(size_t capacity);
	~ParticleVertexArray();

	void draw(Vec2 const* points, Vec4 const* color, size_t size);
protected:
	static const GLuint INVALID_VALUE = 0xFFFFFFFF;
private:
	GLuint mPositionBuffer = INVALID_VALUE;
	GLuint mColorBuffer    = INVALID_VALUE;
	GLuint mVAO            = INVALID_VALUE;
};

} // namespace simple
