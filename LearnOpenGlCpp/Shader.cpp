#include "Shader.h"


Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath) {

	std::ifstream vertexShaderFile{};
	std::ifstream fragmentShaderFile{};

	std::string vertexShaderCode{};
	std::string fragmentShaderCode{};

	// ensure ifstream objects can throw exceptions
	vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		vertexShaderFile.open(vertexPath);
		fragmentShaderFile.open(fragmentPath);

		{
			std::string tmpVertexSource{ (std::istreambuf_iterator<char>{vertexShaderFile}), std::istreambuf_iterator<char>{} };
			std::string tmpFragmentSource{ (std::istreambuf_iterator<char>{fragmentShaderFile}), std::istreambuf_iterator<char>{} };

			vertexShaderFile.close();
			fragmentShaderFile.close();

			vertexShaderCode = std::move(tmpVertexSource);
			fragmentShaderCode = std::move(tmpFragmentSource);
		}
		
	} catch (std::ifstream::failure& e) {
		if (vertexShaderFile.is_open()) {
			vertexShaderFile.close();
		}
		
		if (fragmentShaderFile.is_open()) {
			fragmentShaderFile.close();
		}

		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}


	//===== VERTEX SHADER ========
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	const char * v = vertexShaderCode.c_str();
	glShaderSource(vertexShaderId, 1, &v, nullptr);
	glCompileShader(vertexShaderId);
	ShaderUtil::logShaderStatus(vertexShaderId, GL_COMPILE_STATUS);

	//===== FRAGMENT SHADER ======
	GLuint fragmentShaderid = glCreateShader(GL_FRAGMENT_SHADER);
	const char * f = fragmentShaderCode.c_str();
	glShaderSource(fragmentShaderid, 1, &f, nullptr);
	glCompileShader(fragmentShaderid);
	ShaderUtil::logShaderStatus(fragmentShaderid, GL_COMPILE_STATUS);

	//===== LINK SHADERS TO A SHADER PROGRAM AND RELEASE SHADER RESOURCES
	shaderId = glCreateProgram();
	glAttachShader(shaderId, vertexShaderId);
	glAttachShader(shaderId, fragmentShaderid);
	glLinkProgram(shaderId);
	ShaderUtil::logShaderStatus(shaderId, GL_LINK_STATUS);


	//=== DELETE IN MEMORY SHADERS BECAUSE THEY ARE ALREADY ATTACHED TO THE SHADER PROGRAM
	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderid);
}

void Shader::use() {
	glUseProgram(shaderId);
}

void Shader::setBool(const char* name, bool value) const {
	glUniform1i(glGetUniformLocation(shaderId, name), (int)value);
}

void Shader::setInt(const char* name, int value) const {
	glUniform1i(glGetUniformLocation(shaderId, name), value);
}

void Shader::setFloat(const char* name, float value) const {
	glUniform1f(glGetUniformLocation(shaderId, name), value);
}

void ShaderUtil::logShaderStatus(GLuint shaderId, GLenum statusToCheck) {
	int success;
	char infoLog[512];

	glGetShaderiv(shaderId, statusToCheck, &success); // set success variable based on the link status

	if (!success) {
		glGetShaderInfoLog(shaderId, 512, nullptr, infoLog); // complete infoLog variable
		std::cout << "ERROR::SHADER::" << statusToCheck << std::endl << infoLog << std::endl;
	}
}

