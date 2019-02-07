#pragma once

#include "EngineCommonDependencies.h"
#include <vulkan/vulkan.h>
#include <stdexcept>
#include <functional>
#include <cstdlib>

namespace MyVulkan {

	const int WIDTH = 800;
	const int HEIGHT = 600;

	VkResult createDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);

	void destroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);

	const std::vector<const char*> validationLayers = {
		"VK_LAYER_LUNARG_standard_validation"
	};

	#ifdef NDEBUG
		const bool enableValidationLayers = false;
	#else
		const bool enableValidationLayers = true;
	#endif

	class HelloTriangleApplication {
	public:
		void run();

	private:
		GLFWwindow * window;
		VkInstance instance;
		VkDebugUtilsMessengerEXT debugMessenger;

		void initWindow();
		void initVulkan();
		void mainLoop();
		void cleanup();

		void createIntance();

		bool checkValidationLayerSupport();

		void setupDebugMessenger();

		std::vector<const char*> getRequiredExtensions();
	};
}


