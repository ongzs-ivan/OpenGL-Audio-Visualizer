#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <windows.h>
#include <GL/GLU.h>

#include "camera.h"
#include "matrix.h"
#include "vector.h"

#include "triangle_demo.h"
#include "wave_demo.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// initialize demo.
DemoBase* demo = new TriangleDemo();
//DemoBase* demo = new WaveDemo();

void onWindowResized(GLFWwindow* window, int width, int height)
{
	if (height == 0) height = 1;						// Prevent A Divide By Zero By making Height Equal One

	glViewport(0, 0, width, height);					// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

// Simple camera controller. (MOUSE)
Camera gCamera;
void onMouseMove(GLFWwindow* window, double x, double y)
{
	static int lastX = -1, lastY = -1;
	if (lastX == -1 && lastY == -1)
	{
		lastX = x;
		lastY = y;
		return;
	}

	int offsetX = x - lastX;
	int offsetY = y - lastY;
	lastX = x; lastY = y;

	gCamera.rotate(offsetX * 0.1f, Vector(0.0f, 1.0f, 0.0f));
	gCamera.rotateLocal(offsetY * 0.1f, Vector(1.0f, 0.0f, 0.0f));
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main()
{
	int running = GL_TRUE;

    GLFWwindow* window;

    /* Initialize the GLFW library */
    if (!glfwInit())
        return -1;

	// Open an OpenGL window
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL", NULL, NULL);
	glfwSetKeyCallback(window, keyCallback);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

	// Hook window resize.
	glfwSetWindowSizeCallback(window, onWindowResized);
	   
	/* Make the window's context current */
    glfwMakeContextCurrent(window);

	onWindowResized(window, WINDOW_WIDTH, WINDOW_HEIGHT);

	// hook mouse move callback and lock/hide mouse cursor.
	glfwSetCursorPosCallback(window, onMouseMove);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSwapInterval(1);

	// initialize OpenGL.
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

	// initialize camera.
	gCamera.translate(0.0f, 10.0f, 55.0f);
	gCamera.rotate(10, Vector(1.0f, 0.0f, 0.0f));
	Matrix matrix(Matrix::makeIdentityMatrix());
	Matrix rotateMatrix(Matrix::makeRotateMatrix(0.5f, Vector(0.0f, 1.0f, 0.0f)));

	demo->init();

	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		// OpenGL rendering goes here...
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Simple camera controller. (KEYBOARD)
		float camMoveOffsetX = 0.0f, camMoveOffsetZ = 0.0f;
		if(glfwGetKey(window, 'A')) camMoveOffsetX -= 0.5f;
		if(glfwGetKey(window, 'D')) camMoveOffsetX += 0.5f;
		if(glfwGetKey(window, 'W')) camMoveOffsetZ -= 0.5f;
		if(glfwGetKey(window, 'S')) camMoveOffsetZ += 0.5f;
		gCamera.translateLocal(camMoveOffsetX, 0.0f, camMoveOffsetZ);

		// Check if ESC key was pressed
		if(glfwGetKey(window, GLFW_KEY_ESCAPE))
			break;

		demo->draw(gCamera.getViewMatrix());

		// Swap front and back rendering buffers
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	demo->deinit();
	delete demo;

	// Close window and terminate GLFW
	glfwTerminate();
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_1 && action == GLFW_PRESS)
	{
		demo->SongChanger(1);
	}
	if (key == GLFW_KEY_2 && action == GLFW_PRESS)
	{
		demo->SongChanger(2);
	}
	if (key == GLFW_KEY_3 && action == GLFW_PRESS)
	{
		demo->SongChanger(3);
	}
	if (key == GLFW_KEY_4 && action == GLFW_PRESS)
	{
		demo->SongChanger(4);
	}
	if (key == GLFW_KEY_5 && action == GLFW_PRESS)
	{
		demo->SongChanger(5);
	}
	if (key == GLFW_KEY_6 && action == GLFW_PRESS)
	{
		demo->SongChanger(6);
	}
	if (key == GLFW_KEY_7 && action == GLFW_PRESS)
	{
		demo->SongChanger(7);
	}
}