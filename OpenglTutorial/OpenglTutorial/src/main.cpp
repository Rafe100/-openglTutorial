#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../include/Shader.h"
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
int main() {
	std::cout << "start opengl project" << endl;
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window =  glfwCreateWindow(800,600,"opengltest",NULL, NULL);
	if (window == NULL) {
		std::cout << "fail to create window" << endl;
		glfwTerminate();
		getchar();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		getchar();
		return -1;
	}
	//glViewport(0,0,800,600);
	Shader shader("E:/openglTutorial/-openglTutorial/OpenglTutorial/OpenglTutorial/shader/vertex.vs","E:/openglTutorial/-openglTutorial/OpenglTutorial/OpenglTutorial/shader/fragment.fs");
	float vertices[] = {
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};

	//render loop
	while (!glfwWindowShouldClose(window))
	{
		//input
		processInput(window);

		//äÖÈ¾Ö¸Áî
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	std::cout << "framebuffer size callback:" << endl;
	std::cout << "width:" << width << endl;
	std::cout << "height" << height << endl;
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}