// OpenGL.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GLAD/glad.h"

#include "Module/Camera.h"
#include "Module/Object.h"

#include <GLFW/include/glfw3.h>


#include <iostream>

Camera camera;

double prevX, prevY;
bool first = false;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void cursorPosCallback(GLFWwindow *window, double x, double y)
{
	double xOffset, yOffset, yaw, pitch;
	double sensitive = 0.1f;

	if (false == first)
		first = true;
	else
	{
		xOffset = - (x - prevX) * sensitive;
		yOffset = (y - prevY) * sensitive;

		yaw = camera.getYaw() + xOffset;
		pitch = camera.getPitch() + yOffset;

		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		camera.setYaw(yaw);
		camera.setPitch(pitch);
	}

	prevX = x;
	prevY = y;
}


int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, cursorPosCallback);


    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }



    float vertices[] = {
        0.5f,  0.5f, 0.5f,
        0.5f,  -0.5f, 0.5f,
        -0.5f,  -0.5f, 0.5f,
        -0.5f,  0.5f, 0.5f,

		0.5f,  0.5f, -0.5f,
		0.5f,  -0.5f, -0.5f,
		-0.5f,  -0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
    };

    float texCords[] = {
        1.0f, 1.0f,   // 右上
        1.0f, 0.0f,   // 右下
        0.0f, 0.0f,   // 左下
        0.0f, 1.0f,    // 左上
		1.0f, 1.0f,   // 右上
		1.0f, 0.0f,   // 右下
		0.0f, 0.0f,   // 左下
		0.0f, 1.0f,    // 左上
    };

	int indexs[] = {
		0,2,1,0,3,2,4,1,5,4,0,1,
		4,5,6,4,6,7,3,6,2,3,7,6,
		4,7,3,4,3,0,1,5,6,1,6,2
	};

	Object obj;
    obj.setVertices(vertices, texCords, 8, indexs, 36);
    obj.setTexture("Resource/wall.jpg");

	camera.setEye(glm::vec3(0.0f, 0.0f, 3.0f));

    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // input
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
			camera.move(glm::vec3(0, -0.1, 0));
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
			camera.move(glm::vec3(0, 0.1, 0));
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
			camera.move(glm::vec3(0.1, 0, 0));
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
			camera.move(glm::vec3(-0.1, 0, 0));

        // render
		glEnable(GL_DEPTH_TEST);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        obj.draw(camera.getViewMatrix(), camera.getProjectionMatrix());

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();

    return 0;
}

