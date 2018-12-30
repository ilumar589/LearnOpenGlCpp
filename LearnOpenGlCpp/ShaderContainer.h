#pragma once

#include <string>

class ShaderContainer
{
public:
	ShaderContainer(const char* vertexShaderFileName, const char* fragmentShaderFileName);
	const char * getVertexShaderSource() const;
	const char * getFragmentShaderSource() const;
private:
	std::string vertexShaderSource{};
	std::string fragmentShaderSource{};
};

