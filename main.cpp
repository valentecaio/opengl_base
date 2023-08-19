// g++ main.cpp glad.c -ldl -lglfw -o basics && ./basics

#define GLFW_INCLUDE_NONE

#ifdef _WIN32
#include <windows.h>
#include <gl/gl.h>
#include <GLFW/glfw3.h>
#else
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#endif

#include <iostream>

static void resize(GLFWwindow* win, int width, int height) {
  glViewport(0, 0, width, height);
}

static void cursorpos(GLFWwindow* win, double x, double y) {
  // convert screen pos (upside down) to framebuffer pos
  int win_w, win_h, fb_w, fb_h;
  glfwGetWindowSize(win, &win_w, &win_h);
  glfwGetFramebufferSize(win, &fb_w, &fb_h);
  double fb_x = x * fb_w / win_w;
  double fb_y = (win_h - y) * fb_h / win_h;
  std::cout << "Cursor pos: " << fb_x << ", " << fb_y << std::endl;
}

static void display(GLFWwindow* win) {
  glClear(GL_COLOR_BUFFER_BIT);
  // flush the pipeline so that the commands get executed
  glFlush();
}

static void keyboard(GLFWwindow* win, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(win, GL_TRUE);
  }
}

static void mousebutton(GLFWwindow* win, int button, int action, int mods) {
  if (action == GLFW_PRESS) {
    switch (button) {
      case GLFW_MOUSE_BUTTON_LEFT:
        std::cout << "Left mouse button pressed" << std::endl;
        break;
      case GLFW_MOUSE_BUTTON_MIDDLE:
        std::cout << "Middle mouse button pressed" << std::endl;
        break;
      case GLFW_MOUSE_BUTTON_RIGHT:
        std::cout << "Right mouse button pressed" << std::endl;
        break;
      default:
        std::cout << "Unknown mouse button pressed" << std::endl;
        break;
    }    
  }

  if (action == GLFW_PRESS)
    glfwSetCursorPosCallback(win, cursorpos);
  else
    glfwSetCursorPosCallback(win, nullptr);
}

int main() {
  // init glfw
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // create window and define callbacks
  GLFWwindow* win = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
  glfwSetFramebufferSizeCallback(win, resize);
  glfwSetKeyCallback(win, keyboard);
  glfwSetMouseButtonCallback(win, mousebutton);

  // VERY IMPORTANT FOR GLAD TO WORK
  glfwMakeContextCurrent(win);

  // init glad
  // that's where glad loads the address of openGL functions
  // this address is an OS specific info so we use GLFW to get it
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  // we should be able to use openGL from now on
  std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
  std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

  // init graphics ctx
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glEnable(GL_DEPTH_TEST);

  // main loop
  while (!glfwWindowShouldClose(win)) {
    display(win);
    // double buffer mechanism:
    // we swap the front and back buffers in an atomic operation
    // to avoid flickering issues (images being displayed before
    // rendering is finished)
    glfwSwapBuffers(win);
    // there is an implicit flush after swap
    glfwPollEvents();
  }

  // clean up
  glfwTerminate();
  return 0;
}