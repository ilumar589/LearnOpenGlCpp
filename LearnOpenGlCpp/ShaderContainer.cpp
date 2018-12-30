#include "ShaderContainer.h"

#include <iostream>
#include <fstream>

ShaderContainer::ShaderContainer(const char* vertexShaderFileName, const char* fragmentShaderFileName)
{
	std::ifstream vertexShaderFile{ vertexShaderFileName };
	std::ifstream fragmentShaderFile{ fragmentShaderFileName };

	if (vertexShaderFile.is_open()) {
		std::string tmpVertexSource{ (std::istreambuf_iterator<char>{vertexShaderFile}),
		std::istreambuf_iterator<char>{} };
		this->vertexShaderSource = std::move(tmpVertexSource);
		vertexShaderFile.close();
	}
	else {
		std::cout << "Unable to open file " << vertexShaderFileName << std::endl;
	}
	
	if (fragmentShaderFile.is_open()) {
		std::string tmpFragmentSource{ (std::istreambuf_iterator<char>{fragmentShaderFile}),
		std::istreambuf_iterator<char>{} };
		this->fragmentShaderSource = std::move(tmpFragmentSource);
		fragmentShaderFile.close();
	}
	else {
		std::cout << "Unable to open file " << fragmentShaderFileName << std::endl;
	}
	
}

const char * ShaderContainer::getVertexShaderSource() const
{
	return vertexShaderSource.c_str();
}

const char * ShaderContainer::getFragmentShaderSource() const
{
	return fragmentShaderSource.c_str();
}
