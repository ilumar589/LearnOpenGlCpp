#include "HelloTriangleApplication.h"


void MyVulkan::HelloTriangleApplication::run() {
	initWindow();
	initVulkan();
	mainLoop();
	cleanup();
}

void MyVulkan::HelloTriangleApplication::initWindow() {
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
}

void MyVulkan::HelloTriangleApplication::initVulkan() {
}

void MyVulkan::HelloTriangleApplication::mainLoop() {
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	}
}

void MyVulkan::HelloTriangleApplication::cleanup() {
	glfwDestroyWindow(window);
	glfwTerminate();
}
