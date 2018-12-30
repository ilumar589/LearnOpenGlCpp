#include<glad/glad.h>
#include <Glfw3/glfw3.h>
#include<iostream>

// global shaders
const char * vertex_shader_source = "#version 330 core\n"
"layout (location=0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\n\0";

const char * fragment_shader_source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGl", nullptr, nullptr);

	if (!window) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);
	
	// Setup shaders
	// --------------

	unsigned int vertex_shader;
	vertex_shader = glCreateShader(GL_VERTEX_SHADER); // create vertex shader

	glShaderSource(vertex_shader, 1, &vertex_shader_source, nullptr); // bind shader to shader source; function requires pointer to a pointer for some reason
	glCompileShader(vertex_shader); //compile shader

	// vertex shader compilation check
	{
		int success;
		char infoLog[512];

		glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success); // set success variable based on the compile status

		if (!success) {
			glGetShaderInfoLog(vertex_shader, 512, nullptr, infoLog); // complete infoLog variable
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
	}

	unsigned int fragment_shader;
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

	// fragment shader compilation check
	{
		int success;
		char infoLog[512];

		glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success); // set success variable based on the compile status

		if (!success) {
			glGetShaderInfoLog(fragment_shader, 512, nullptr, infoLog); // complete infoLog variable
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
	}

	glShaderSource(fragment_shader, 1, &fragment_shader_source, nullptr); // bind shader to shader source; function requires pointer to a pointer for some reason
	glCompileShader(fragment_shader); //compile shader

	// create shader program which will link all the used shaders
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertex_shader);
	glAttachShader(shaderProgram, fragment_shader);
	glLinkProgram(shaderProgram);

	// shader program check
	{
		int success;
		char infoLog[512];

		glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success); // set success variable based on the link status

		if (!success) {
			glGetShaderInfoLog(shaderProgram, 512, nullptr, infoLog); // complete infoLog variable
			std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
		}
	}

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	// setup triangle vertices
	float triangle_vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	unsigned int VAO,VBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO); // assign the OpenGL buffer type GL_ARRAY_BUFFER to the vertex buffer object
										// from now on each call we make to this type will use the VBO

	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW); // copy the triangle vertices into the vertex buffers object memory

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window)) {

		// input
		processInput(window);

		// rendering commands here
		glUseProgram(shaderProgram); // set OpenGL to use the shader program; !TODO use in loop
		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		glDrawArrays(GL_TRIANGLES, 0, 3);


		// check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	glfwTerminate();

	return 0;
}

void frameBufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
		glfwSetWindowShouldClose(window, true);
	}
}