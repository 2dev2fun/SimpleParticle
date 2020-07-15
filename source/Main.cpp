#include "Particle/System.h"
#include "Shader/Particle.h"
#include "VertexArray/Particle.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cstdint>
#include <cmath>
#include <stdexcept>
#include <string>
#include <vector>
#include <memory>
#include <thread>
#include <chrono>

using namespace simple;

const uint32_t SCR_WIDTH = 800;
const uint32_t SCR_HEIGHT = 600;

const size_t gEffects   = 2048;
const size_t gParticles = 64;

ParticleSystem<gEffects, gParticles> gParticleSystem;

double gMouseXPosition = 0.0f;
double gMouseYPosition = 0.0f;

void key_callback(GLFWwindow* window, int key, int /*scancode*/, int action, int /*mods*/) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int /*mods*/) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		double xpos = 0;
		double ypos = 0;

		glfwGetCursorPos(window, &xpos, &ypos);

		xpos /= SCR_WIDTH;
		ypos /= SCR_HEIGHT;

		xpos = xpos >= 0 ? xpos : 0;
		xpos = xpos <= 1 ? xpos : 1;

		ypos = ypos >= 0 ? ypos : 0;
		ypos = ypos <= 1 ? ypos : 1;

		xpos -= 0.5f;
		ypos -= 0.5f;

		ypos *= -1;

		xpos *= 2;
		ypos *= 2;

		gParticleSystem.emit(xpos, ypos);
	}
}

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Test task", nullptr, nullptr);
	if (window == nullptr) {
		std::cout << "Failed to create GLFW window!" << std::endl;
		glfwTerminate();
		return 0;
	}
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD!" << std::endl;
		return 0;
	}

	glEnable(GL_PROGRAM_POINT_SIZE);
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

	auto shader = std::make_unique<ParticleShader>();
	auto vertexArray = std::make_unique<ParticleVertexArray>(gEffects * gParticles);

	using namespace std::chrono;
	using namespace std::chrono_literals;
	using namespace std::this_thread;

	auto previousFrame = high_resolution_clock::now();
	auto lag = previousFrame - previousFrame;
	auto referenceFrame = microseconds(16'672);

	while (!glfwWindowShouldClose(window)) {
		auto startFrame = high_resolution_clock::now();
		lag += startFrame - previousFrame;
		previousFrame = startFrame;

		while (lag >= referenceFrame) {
			lag -= referenceFrame;
		}

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader->active();
		shader->setPointSize(10.0f);

		auto* position = gParticleSystem.getPosition().data();
		auto* color    = gParticleSystem.getColor().data();
		auto  size     = gParticleSystem.size();

		vertexArray->draw(position, color, size);

		gParticleSystem.update(16.0f / 1000.0f);

		auto endFrame = high_resolution_clock::now();
		if ((endFrame - startFrame) < referenceFrame) {
			auto sleepTime = startFrame + referenceFrame - endFrame;
			sleep_for(sleepTime);
		}

		//auto frameTime = duration_cast<microseconds>(high_resolution_clock::now() - startFrame).count();
		//std::cout << "frame time:\t" << frameTime << " μs." << std::endl;

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	shader.release();
	vertexArray.release();

	glfwTerminate();

	return 0;
}
