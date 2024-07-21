if (TARGET glad)
  return()
endif()

set(url_repository "https://github.com/SasLuca/MyGlad.git")

include(FetchContent)

FetchContent_Declare(glad
GIT_REPOSITORY "${url_repository}"
GIT_TAG master)

FetchContent_MakeAvailable(glad)