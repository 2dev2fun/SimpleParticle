#include "Shader/Particle.h"

namespace simple {

ParticleShader::ParticleShader() {
	attachVS("shader/Particle.vs");
	attachFS("shader/Particle.fs");

	compile();
	active();

	mPointSize = getUniform("uPointSize");
}

} // namespace simple
