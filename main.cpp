#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "dependente\glew\glew.h"
#include "dependente\glfw\glfw3.h"
#include "dependente\glm\glm.hpp"
#include "dependente\glm\gtc\matrix_transform.hpp"
#include "dependente\glm\gtc\type_ptr.hpp"
#include "shader.hpp"


GLFWwindow* window;
const int width = 1024, height = 1024;


void window_callback(GLFWwindow* window, int new_width, int new_height)
{
	glViewport(0, 0, new_width, new_height);
}

glm::mat4 trans(1.0f);

glm::vec3 positions[] =
{
	glm::vec3(-0.17f,  0.3f, 0),
	glm::vec3(0.2f,  0.5f, 0),
	glm::vec3(0.15f,  0.7f, 0),
	glm::vec3(-0.38f, -0.2f, 0),
	glm::vec3(0.24f, -0.4f, 0),
	glm::vec3(0.0f,  0.0f,  0),
	glm::vec3(0.23f, -0.2f, 0),
	glm::vec3(0.15f,  0.2f, 0),
	glm::vec3(-0.15f, -0.22f, 0),
	glm::vec3(-0.13f,  0.14f, 0)
};

int aux = 0;
bool flag3 = false;
bool flag = false;
bool flag2 = false;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_T && action == GLFW_PRESS)
	{
		flag2 = !flag2;
	}

	if ((key == GLFW_KEY_B || key == GLFW_KEY_N || key == GLFW_KEY_M) && action == GLFW_PRESS)
	{
		aux = aux + 1;
	}

	glm::mat4 trans2 = glm::mat4(1.0f);
	if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		flag3 = !flag3;
	}

	if (key == GLFW_KEY_C && action == GLFW_PRESS)
	{
		trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
	}

	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
	{
		flag = !flag;
	}
}


int main(void)
{
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(width, height, "Lab 4", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window.");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		glfwTerminate();
		return -1;
	}

	//specify the size of the rendering window
	glViewport(0, 0, width, height);

	// background color
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	GLuint programID = LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");

	//Square
	GLfloat vertices[] =
	{
		0.2f,  0.2f, 0.0f,
		0.2f, -0.2f, 0.0f,
		-0.2f, -0.2f, 0.0f,
		-0.2f,  0.2f, 0.0f
	};

	//Square
	GLuint indices[] =
	{
		0, 3, 1,
		1, 3, 2
	};


	//HEX
	GLfloat verticesHex[] =
	{
		-0.1f, -0.2f, 0.0f,
		-0.25f, 0.0f, 0.0f,
		-0.1f, 0.2f, 0.0f,
		0.1f, 0.2f, 0.0f,
		0.25f, 0.0f, 0.0f,
		0.1f, -0.2f, 0.0f
	};

	//HEX
	GLuint indicesHex[] =
	{
		1, 2, 0,
		2, 0, 3,
		0, 3, 5,
		3, 5, 4
	};


	//oct
	GLfloat verticesOct[] =
	{
		0.1f, 0.2f, 0.0f,
		0.2f, 0.1f, 0.0f,
		0.2f, -0.1f, 0.0f,
		0.1f, -0.2f, 0.0f,
		-0.1f, -0.2f, 0.0f,
		-0.2f, -0.1f, 0.0f,
		-0.2f, 0.1f, 0.0f,
		-0.1f, 0.2f, 0.0f
	};

	//oct
	GLuint indicesOct[] =
	{
		3, 4, 5,
		3, 5, 2,
		5, 6, 2,
		2, 6, 1,
		1, 6, 7,
		1, 7, 0
	};

	GLuint vbo, vao, ibo;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);


	glfwSetFramebufferSizeCallback(window, window_callback);
	glfwSetKeyCallback(window, key_callback);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode
	float counter = 0.0f;
	while (!glfwWindowShouldClose(window))
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glVertexAttribPointer(
			0,                  // attribute 0, must match the layout in the shader.
			3,                  // size of each attribute
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			3 * sizeof(float),  // stride
			(void*)0            // array buffer offset
		);
		glEnableVertexAttribArray(0);
		glDrawElements(GL_TRIANGLES, 365, GL_UNSIGNED_INT, 0);

		//square draw on key input "B"
		if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
		{
			trans = glm::translate(glm::mat4(1.0f), positions[aux % 10]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		}

		//hex draw on key input "N"
		if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
		{
			trans = glm::translate(glm::mat4(1.0f), positions[aux % 10]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(verticesHex), verticesHex, GL_STATIC_DRAW);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesHex), indicesHex, GL_STATIC_DRAW);
		}

		//oct draw on key input "M"
		if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
		{
			trans = glm::translate(glm::mat4(1.0f), positions[aux % 10]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(verticesOct), verticesOct, GL_STATIC_DRAW);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesOct), indicesOct, GL_STATIC_DRAW);
		}

		// rotation over time (toggle)
		if (flag == true)
		{
			trans = glm::rotate(trans, -1.0f, glm::vec3(0.0, 0.0, 66.0));
		}

		//For tranlation "animation"
		if (flag2 == true)
		{
			trans = glm::translate(glm::mat4(1.0f), positions[aux % 10]);
			positions[aux % 10].x = sinf(counter) / 1.25;
			counter += 0.01f;
		}

		// scaling (toggle)
		if (flag3 == true)
		{
			trans = glm::scale(trans, glm::vec3(1.01, 1.01, 1.01));
		}


		glfwSwapBuffers(window);
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(programID);
		glBindVertexArray(vao);


		unsigned int transformLoc = glGetUniformLocation(programID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

		unsigned int transformLoc2 = glGetUniformLocation(programID, "color");
		glm::vec4 color = glm::vec4(1.0f, 1.0, 1.0f, 0.0); //object color
		glUniform4fv(transformLoc2, 1, glm::value_ptr(color));


		//key input "O" for clearing screen;
		if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		{
			glDeleteBuffers(1, &vbo);
			glDeleteBuffers(1, &ibo);
			glDeleteVertexArrays(1, &vao);
			glDeleteProgram(programID);
		}
	}

	glfwTerminate();
	return 0;
}