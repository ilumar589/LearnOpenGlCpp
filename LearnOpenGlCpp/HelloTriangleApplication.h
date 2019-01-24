#pragma once

#include "EngineCommonDependencies.h"
#include <vulkan/vulkan.h>
#include <stdexcept>
#include <functional>
#include <cstdlib>

namespace MyVulkan {

	const int WIDTH = 800;
	const int HEIGHT = 600;

	class HelloTriangleApplication {
	public:
		void run();

	private:
		GLFWwindow * window;

		void initWindow();
		void initVulkan();
		void mainLoop();
		void cleanup();
	};
}


