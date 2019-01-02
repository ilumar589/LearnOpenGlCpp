#include "TwoTrianglesExample.h"
#include "ShaderContainer.h"

void TwoTrianglesExample::executeExample() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGl", nullptr, nullptr);

	if (!window) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);

	//===== SHADER SETUP ========

	ShaderContainer shaderContainer{"VertexShaderT2.glsl", "FragmentShaderT2.glsl"};

	//===== VERTEX SHADER ========
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	const char * vertexShaderSource = shaderContainer.getVertexShaderSource();
	glShaderSource(vertexShaderId, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShaderId);
	logShaderStatus(vertexShaderId, GL_COMPILE_STATUS);

	//===== FRAGMENT SHADER ======
	GLuint fragmentShaderid = glCreateShader(GL_FRAGMENT_SHADER);
	const char * fragmentShaderSource = shaderContainer.getFragmentShaderSource();
	glShaderSource(fragmentShaderid, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShaderid);
	logShaderStatus(fragmentShaderid, GL_COMPILE_STATUS);

	//===== LINK SHADERS TO A SHADER PROGRAM AND RELEASE SHADER RESOURCES
	GLuint shaderProgramId = glCreateProgram();
	glAttachShader(shaderProgramId, vertexShaderId);
	glAttachShader(shaderProgramId, fragmentShaderid);
	glLinkProgram(shaderProgramId);
	logShaderStatus(shaderProgramId, GL_LINK_STATUS);

	//=== DELETE IN MEMORY SHADERS BECAUSE THEY ARE ALREADY ATTACHED TO THE SHADER PROGRAM
	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderid);

	//======= DEFINE TRIANGLE DATA ========

	float firstTriangle[] = {
		-0.5f, 0.5f, 0.0f, // top first triangle
		-1.0f, 0.0f, 0.0f, // left first triangle
		0.0f, 0.0f, 0.0f // right first triangle
	};

	float secondTriangle[] = {
		0.5f, 0.5f, 0.0f, // top second triangle
		0.0f, 0.0f, 0.0f, // left second triangle
		1.0f, 0.0f, 0.0f // right second triangle
	};

	GLuint vaoIdArray[2], baoIdArray[2];

	glGenVertexArrays(2, vaoIdArray);
	glGenBuffers(2, baoIdArray);

	//==== FIRST VERTEX ARRAY AND BUFFER ARRAY OBJECT ====
	glBindVertexArray(vaoIdArray[0]);
	glBindBuffer(GL_ARRAY_BUFFER, baoIdArray[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//==== SECOND VERTEX ARRAY AND BUFFER ARRAY OBJECT ====
	glBindVertexArray(vaoIdArray[1]);
	glBindBuffer(GL_ARRAY_BUFFER, baoIdArray[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window)) {

		// input
		processInput(window);

		// rendering commands here
		glUseProgram(shaderProgramId);

		glBindVertexArray(vaoIdArray[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(vaoIdArray[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	glfwTerminate();
}

void TwoTrianglesExample::frameBufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void TwoTrianglesExample::processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
		glfwSetWindowShouldClose(window, true);
	}
}

void TwoTrianglesExample::logShaderStatus(GLuint shaderId, GLenum statusToCheck) {
	int success;
	char infoLog[512];

	glGetShaderiv(shaderId, statusToCheck, &success); // set success variable based on the link status

	if (!success) {
		glGetShaderInfoLog(shaderId, 512, nullptr, infoLog); // complete infoLog variable
		std::cout << "ERROR::SHADER::" << statusToCheck << std::endl << infoLog << std::endl;
	}
}