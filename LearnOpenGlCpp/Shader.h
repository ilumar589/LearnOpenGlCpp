#pragma once

#include "EngineCommonDependencies.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

	GLuint shaderId;

	void use();

	// utility uniform functions
	void setBool(const char* name, bool value) const;
	void setInt(const char* name, int value) const;
	void setFloat(const char* name, float value) const;
};


// associate functions for the Shader class
namespace ShaderUtil {
	void logShaderStatus(GLuint shaderId, GLenum statusToCheck);
}

