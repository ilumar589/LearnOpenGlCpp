#pragma once

#include "EngineCommonDependencies.h"

namespace MoreThanOneAttributeExample {
	void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
	void processInput(GLFWwindow* window);
	void logShaderStatus(GLuint shaderId, GLenum statusToCheck);
	void executeExample();
}