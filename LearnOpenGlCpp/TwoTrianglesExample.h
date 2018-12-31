#pragma once

#include<glad/glad.h>
#include <Glfw3/glfw3.h>
#include<iostream>

namespace TwoTrianglesExample {

	void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
	void processInput(GLFWwindow* window);
	void logShaderStatus(GLuint shaderId, GLenum statusToCheck);
	void executeExample();
}