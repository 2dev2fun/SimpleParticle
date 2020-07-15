#pragma once

#include "Shader.h"

namespace simple {

class ParticleShader : public Shader {
public:
	ParticleShader();
	~ParticleShader() {};

	void setPointSize(float value);
private:
	GLuint mPointSize = INVALID_VALUE;
};

inline void ParticleShader::setPointSize(float value) {
	setFloat(mPointSize, value);
}

} // namespace simple
