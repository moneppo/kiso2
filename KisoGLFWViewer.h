#ifndef KISOGLFWVIEWER
#define KISOGLFWVIEWER

#include <iostream>
#ifdef __APPLE__
	#define GLFW_INCLUDE_GLCOREARB
#endif
#include <GLFW/glfw3.h>
#include "nanovg.h"

#include "KisoRenderer.h"
#include "KisoApp.h"

#define NANOVG_GL3_IMPLEMENTATION
#include "vector.h"

using namespace std;

class KisoGLFWViewer {
public:
	KisoGLFWViewer(bool debug = false) {
		if (!glfwInit()) {
			cerr << "Failed to init GLFW." << endl;
			throw -1;
		}
		
		m_window = glfwCreateWindow(1000, 600, "NanoVG", NULL, NULL);
		if (!m_window) {
			glfwTerminate();
			cerr << "Failed to created GLFW window." << endl;
			throw -1;
		}
		
		glfwSetKeyCallback(m_window, keyEvent);
		glfwMakeContextCurrent(m_window);
				
		glfwGetWindowSize(m_window, &m_windowSize.x, &m_windowSize.y);
		glfwGetFramebufferSize(m_window, &m_frameBufferSize.x, &m_frameBufferSize.x);
		m_aspectRatio = (float)m_frameBufferSize.x / (float)m_frameBufferSize.x;

		glViewport(0, 0, m_frameBufferSize.x, m_frameBufferSize.y);
		
		m_renderer = new KisoRenderer(m_windowSize, m_aspectRatio, debug);
	}
	
	virtual ~KisoGLFWViewer() {
		delete m_renderer;
		glfwTerminate();
	}
	
	int run(KisoApp* app) {
		while (!glfwWindowShouldClose(m_window))
		{
			glfwGetCursorPos(m_window, &m_mouse.x, &m_mouse.y);

			m_renderer->render(app);

			glfwSwapBuffers(m_window);
			
			glfwPollEvents();
		}
		return 0;
	}
	
protected:
	static void keyEvent(GLFWwindow* window, int key, int scancode, int action, int mods)
	{	
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
	}
	
	GLFWwindow* m_window;

	vec2d m_mouse;
	vec2i m_windowSize;
	vec2i m_frameBufferSize;
	float m_aspectRatio;
	
	KisoRenderer* m_renderer;
};

#endif