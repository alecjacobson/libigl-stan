cmake_minimum_required(VERSION 3.16)
project(example)

list(PREPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# stan requires c++14 and constexpr is in 17 and templated lambda in 20
set(CMAKE_CXX_STANDARD 20)

# Libigl
include(libigl)

igl_include(glfw)

include(stan)

# Link igl (and the glfw module) to your project
target_link_libraries(${PROJECT_NAME} PUBLIC 
  stan::stan
  igl::glfw
  )
