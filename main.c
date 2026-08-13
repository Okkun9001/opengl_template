#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

#define DEFAULT_SCREEN_WIDTH 1920
#define DEFAULT_SCREEN_HEIGHT 1080

void MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
                     GLsizei length, const GLchar *message,
                     const void *userParam) {
  (void)source;
  (void)id;
  (void)length;
  (void)userParam;
  fprintf(stderr,
          "GL CALLBACK: %s type == 0x%x, severity = 0x%x, message = %s\n",
          (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""), type, severity,
          message);
}

void error_callback(int error, const char *description) {
  fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action,
                         int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

static void window_size_callback(void) {}

int main() {

  glfwSetErrorCallback(error_callback);
  if (!glfwInit()) {
    fprintf(stderr, "ERROR: could not initialize GLFW\n");
    exit(1);
  }

  printf("GLFW initialized\n");
  printf("Platform: %s\n", glfwGetPlatform() == GLFW_PLATFORM_WAYLAND
                               ? "Wayland"
                           : glfwGetPlatform() == GLFW_PLATFORM_X11 ? "X11"
                                                                    : "Other");

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  GLFWwindow *const window =
      glfwCreateWindow(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT,
                       "OpenGL Template", NULL, NULL);

  if (!window) {
    fprintf(stderr, "ERROR: could not create window. \n");
    glfwTerminate();
    exit(1);
  }

  if (glDebugMessageCallback != NULL) {
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, 0);
  }
  // set key callbacks
  glfwSetKeyCallback(window, key_callback);
  // glfwSetFramebufferSizeCallback(window, window_size_callback);

  glfwMakeContextCurrent(window);

  int gl_ver_major = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MAJOR);
  int gl_ver_minor = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MINOR);
  printf("OpenGL %d.%d\n", gl_ver_major, gl_ver_minor);

  // initialize extension loader libraries here to access modern opengl
  if (!gladLoadGL(glfwGetProcAddress)) {
    fprintf(stderr, "ERROR: failed to initialize GLAD\n");
    glfwDestroyWindow(window);
    glfwTerminate();
    return 1;
  }

  double prev_time = 0.0;
  double delta_time = 0.0f;

  // closing a button is just a suggestion, not a command
  while (!glfwWindowShouldClose(window)) {

    // Set frame buffer
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    const float ratio = width / (float)height;

    // Keep running
    glfwPollEvents();

    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);

    double cur_time = glfwGetTime();
    delta_time = cur_time - prev_time;
    prev_time = cur_time;
  }
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
