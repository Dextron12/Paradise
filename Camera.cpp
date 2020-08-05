#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Camera.hpp"

#include <iostream>

extern GLFWwindow* window;

glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;

glm::mat4 getViewMatrix() {
	return ViewMatrix;
}

glm::mat4 getProjectionMatrix() {
	return ProjectionMatrix;
}

glm::vec3 position = glm::vec3(0, 0, 5);
float horizontalAngle = 3.14f;
float verticalAngle = 0.0f;
float initialFoV = 45.0f;

float speed = 3.0f;
float mouseSpeed = 0.002f;

const char keyPreference[] = "wasd";

void computeMatricesFromInputs() {
	static double lastTime = glfwGetTime();

	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);



	glfwSetCursorPos(window, 1024 / 2, 700 / 2);
	
	horizontalAngle += mouseSpeed * float(1024 / 2 - xpos);
	if (verticalAngle > -1.5f) {
		verticalAngle += mouseSpeed * float(700 / 2 - ypos);
	}
	else {
		verticalAngle -= mouseSpeed * float(700 / 2 - ypos);
	}
	//verticalAngle += mouseSpeed * float(700 / 2 - ypos);

	//std::cout << verticalAngle << std::endl;


	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	//right vector
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f / 2.0f)
	);

	//up vector
	glm::vec3 up = glm::cross(right, direction);

	//move foward
	if (keyPreference == "wasd") {
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
			position += direction * deltaTime * speed;
		}
		//move backward
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
			position -= direction * deltaTime * speed;
		}
		//move right
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
			position += right * deltaTime * speed;
		}
		//move left
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
			position -= right * deltaTime * speed;
		}
	}
	else {
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			position += direction * deltaTime * speed;
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			position -= direction * deltaTime * speed;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			position += right * deltaTime * speed;
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			position -= right * deltaTime * speed;
		}
	}

	//stop
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}



	float Fov = initialFoV; //disbaled !!! REQUIRES CALLBACK FUNCTION TO CREATE A ZOOM SHOULD BE: float FoV - 5 * funcCallback

	ProjectionMatrix = glm::perspective(glm::radians(Fov), 4.0f / 3.0f, 0.1f, 100.0f);
	// camera matrix
	ViewMatrix = glm::lookAt(
		position, //camera is here
		position + direction, //and looks here
		up //head is up
	);

	lastTime = currentTime;

}