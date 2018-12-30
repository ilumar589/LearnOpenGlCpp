#pragma

#include<glad/glad.h>
#include <Glfw3/glfw3.h>
#include<iostream>

#include "ShaderContainer.h"

int main() {
	ShaderContainer shaderContainer{ "vertexShaderT1.txt", "fragmentShaderT1.txt" };

	std::cout << shaderContainer.getVertexShaderSource();

	return 0;
}