#include "VertexArray/Particle.h"

#include <iostream>
#include <vector>

namespace simple {

ParticleVertexArray::ParticleVertexArray(size_t capacity) {
	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);

	glGenBuffers(1, &mPositionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mPositionBuffer);
	glBufferData(GL_ARRAY_BUFFER, capacity * sizeof(Vec2), nullptr, GL_STREAM_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vec2), reinterpret_cast<void*>(0));

	glGenBuffers(1, &mColorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mColorBuffer);
	glBufferData(GL_ARRAY_BUFFER, capacity * sizeof(Vec4), nullptr, GL_STREAM_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vec4), reinterpret_cast<void*>(0));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

ParticleVertexArray::~ParticleVertexArray() {
	if (mPositionBuffer != INVALID_VALUE) {
		glDeleteBuffers(1, &mPositionBuffer);
		mPositionBuffer = INVALID_VALUE;
	}

	if (mColorBuffer != INVALID_VALUE) {
		glDeleteBuffers(1, &mColorBuffer);
		mColorBuffer = INVALID_VALUE;
	}

	if (mVAO != INVALID_VALUE) {
		glDeleteVertexArrays(1, &mVAO);
		mVAO = INVALID_VALUE;
	}
}

void ParticleVertexArray::draw(Vec2 const* position, Vec4 const* color, size_t size) {
	if (size > 0) {
		glBindBuffer(GL_ARRAY_BUFFER, mPositionBuffer);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size * sizeof(Vec2), position);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ARRAY_BUFFER, mColorBuffer);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size * sizeof(Vec4), color);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(mVAO);
		glDrawArrays(GL_POINTS, 0, size);
		glBindVertexArray(0);
	}
}

} // namespace simple
