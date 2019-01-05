#include "MoreThanOneAttributeExample.h"
#include "Shader.h"
#include <iostream>

void MoreThanOneAttributeExample::executeExample() {
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

	Shader shader{"vertexShaderT1.txt", "fragmentShaderT1.txt"};

	// setup triangle vertices
	float triangle_vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	unsigned int VAO, VBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO); // assign the OpenGL buffer type GL_ARRAY_BUFFER to the vertex buffer object
										// from now on each call we make to this type will use the VBO

	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW); // copy the triangle vertices into the vertex buffers object memory

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // tell OpenGL how the attribute 
									// pointing to the currently bound vbo should interpret the data
									// in this case vertex attribute 0 from the currently bounded vao
	glEnableVertexAttribArray(0); // enable vertex attribute 0

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window)) {

		// input
		processInput(window);

		// rendering commands here
		shader.use(); // set OpenGL to use the shader program; !TODO use in loop
		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		glDrawArrays(GL_TRIANGLES, 0, 3);


		// check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	glfwTerminate();
}

void MoreThanOneAttributeExample::frameBufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void MoreThanOneAttributeExample::processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
		glfwSetWindowShouldClose(window, true);
	}
}


void MoreThanOneAttributeExample::logShaderStatus(GLuint shaderId, GLenum statusToCheck) {
	int success;
	char infoLog[512];

	glGetShaderiv(shaderId, statusToCheck, &success); // set success variable based on the link status

	if (!success) {
		glGetShaderInfoLog(shaderId, 512, nullptr, infoLog); // complete infoLog variable
		std::cout << "ERROR::SHADER::" << statusToCheck << std::endl << infoLog << std::endl;
	}
}
