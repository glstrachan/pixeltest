cmake_minimum_required(VERSION 3.5)
project(PixelTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include)

# Find required packages
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

include(FetchContent)

# Fetch GLM
FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG        bf71a834948186f4097caa076cd2663c69a10e1e
)
FetchContent_MakeAvailable(glm)

# Fetch GLEW
FetchContent_Declare(
  glew
  GIT_REPOSITORY https://github.com/Perlmint/glew-cmake.git
  GIT_TAG        origin/master
)
FetchContent_GetProperties(glew)
if(NOT glew_POPULATED)
  FetchContent_Populate(glew)
  add_subdirectory(${glew_SOURCE_DIR} ${glew_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

# Fetch stb
FetchContent_Declare(
  stb
  GIT_REPOSITORY https://github.com/nothings/stb.git
  GIT_TAG        master
)
FetchContent_GetProperties(stb)
if(NOT stb_POPULATED)
  FetchContent_Populate(stb)
  include_directories(${stb_SOURCE_DIR})
endif()

# Fetch EnTT
FetchContent_Declare(
  entt
  GIT_REPOSITORY https://github.com/skypjack/entt.git
  GIT_TAG v3.12.2
)
FetchContent_MakeAvailable(entt)


# Include directories for OpenGL and GLFW
include_directories(${OPENGL_INCLUDE_DIR})

# Automatically include all files in the src directory
file(GLOB PROJECT_SOURCES "src/*.cpp")

# Define the executable with the collected source files
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

# Link the executable with OpenGL, GLFW, GLEW, and GLM
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} glfw libglew_static EnTT::EnTT)