#include "VulkanMain.h"
#include "HelloTriangleApplication.h"
#include <glm.hpp>

void MyVulkan::main() {
	HelloTriangleApplication app;

	try {
		app.run();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
}