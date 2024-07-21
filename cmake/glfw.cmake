if (TARGET glfw)
  return()
endif()

set(url_repository "https://github.com/glfw/glfw.git")

include(FetchContent)

FetchContent_Declare(glfw
GIT_REPOSITORY "${url_repository}"
GIT_TAG 3.4)

set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_DOCS OFF)

FetchContent_MakeAvailable(glfw)