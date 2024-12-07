#include "GLFWCallbacks.h"
#include "ApplicationHarness.h"

#define ZOOM_FACTOR 1.2f

void WindowResizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	ApplicationHarness* programPointer = (ApplicationHarness*)glfwGetWindowUserPointer(window);

	switch (action) {
	case GLFW_PRESS: {
		programPointer->OnKey(key, 'a');
		break;
	}
	case GLFW_RELEASE: {
		programPointer->OnKey(key, 'b');
		break;
	}
	case GLFW_REPEAT: {
		programPointer->OnKey(key, 'c');
		break;
	}
	}

}

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	ApplicationHarness* programPointer = (ApplicationHarness*)glfwGetWindowUserPointer(window);	//This is an unsafe coercive cast, but we just have to be careful and live with it.
	if (action == GLFW_PRESS)
	{
		programPointer->OnMouseClick(button);
	}
	else if (action == GLFW_RELEASE)
	{
		//We don't just do 'else' here because 'action' can also be GLFW_REPEAT. Operating systems send this when a button or key is held down, depending on the settings, but we're going to ignore it.
		programPointer->OnMouseRelease(button);
	}
}

void MouseWheelCallback(GLFWwindow* window, double xDelta, double yDelta)
{
	ApplicationHarness* programPointer = (ApplicationHarness*)glfwGetWindowUserPointer(window);
	if (yDelta > 0)
	{
		programPointer->Zoom(ZOOM_FACTOR);
	}
	else
	{
		programPointer->Zoom(1.0f / ZOOM_FACTOR);
	}
}
