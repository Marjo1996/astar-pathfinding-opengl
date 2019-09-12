#include "window.h"

myWindow::myWindow()
{
}

void myWindow::init() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	mainWindow = glfwCreateWindow(sizeX, sizeY, "A* Pathfinding", nullptr, nullptr); // Windowed
	glfwMakeContextCurrent(mainWindow);

	create_callbacks(); // handle key + mouse input

	// Initialize GLEW to setup the OpenGL Function pointers
	glewExperimental = GL_TRUE;
	glewInit();

	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	// Define the viewport dimensions
	glViewport(0, 0, bufferWidth, bufferHeight);

	glfwSetWindowUserPointer(mainWindow, this); // this function is for taking inputs

	// Set OpenGL options
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void myWindow::clear_buffers() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	if (glfwWindowShouldClose(mainWindow)) {
		GLB::WINDOW_CLOSE = true;
	}
}

void myWindow::create_callbacks() { // important for taking the keyboard / mouse input 
	glfwSetKeyCallback(mainWindow, handle_keys);
	glfwSetCursorPosCallback(mainWindow, handle_mouse);
	glfwSetMouseButtonCallback(mainWindow, mouse_button_callback);
}

void myWindow::handle_keys(GLFWwindow* window, int key, int code, int action, int mode) 
{
	myWindow* theWindow = static_cast<myWindow*>(glfwGetWindowUserPointer(window));

	// ESC CLOSES THE WINDOW if pressed on main menu
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		GLB::WINDOW_CLOSE = true;
	}
	if ((key == GLFW_KEY_ENTER)) {
		if (action == GLFW_PRESS) {
			GLB::ENTER = true;
		}
		else if (action == GLFW_RELEASE) {
			GLB::ENTER = false;
		}
	}
	if ((key == GLFW_KEY_LEFT_CONTROL || key == GLFW_KEY_RIGHT_CONTROL)) {
		if (action == GLFW_PRESS) {
			GLB::CTRL = true;
		}
		else if (action == GLFW_RELEASE) {
			GLB::CTRL = false;
		}
	}
	if ((key == GLFW_KEY_LEFT_ALT)) {
		if (action == GLFW_PRESS) {
			GLB::ALT = true;
		}
		else if (action == GLFW_RELEASE) {
			GLB::ALT = false;
		}
	}
	if ((key == GLFW_KEY_N)) {
		if (action == GLFW_PRESS) {
			GLB::KEY_N = true;
		}
		else if (action == GLFW_RELEASE) {
			GLB::KEY_N = false;
		}
	}
	if ((key == GLFW_KEY_SPACE)) {
		if (action == GLFW_PRESS) {
			GLB::SPACE = !GLB::SPACE;
		}
	}
}

void myWindow::handle_mouse(GLFWwindow* window, double xPos, double yPos)
{
	myWindow* theWindow = static_cast<myWindow*>(glfwGetWindowUserPointer(window));
	theWindow->lastX = xPos;
	double y = fabs(yPos - sizeY);
	theWindow->lastY = y;

}

void myWindow::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	myWindow* theWindow = static_cast<myWindow*>(glfwGetWindowUserPointer(window));

	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		if (action == GLFW_PRESS) {
			GLB::MOUSE_LEFT = true;
			GLB::MOUSE_RELEASE = false;
		}
		else if (action == GLFW_RELEASE) {
			GLB::MOUSE_LEFT = false;
			GLB::MOUSE_RELEASE = true;
		}
	}
	if (button == GLFW_MOUSE_BUTTON_RIGHT) {
		if (action == GLFW_PRESS) {
			GLB::MOUSE_RIGHT = true;
			GLB::MOUSE_RELEASE = false;
		}
		else if (action == GLFW_RELEASE) {
			GLB::MOUSE_RIGHT = false;
			GLB::MOUSE_RELEASE = true;
		}
	}
}

myWindow::~myWindow()
{
}
