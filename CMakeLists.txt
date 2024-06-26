cmake_minimum_required(VERSION 3.5.0)
project(sandbox VERSION 0.1.0 LANGUAGES C CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")


find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)
add_executable(sandbox main.cpp)
target_link_libraries(sandbox ${OPENGL_glu_LIBRARY})
target_link_libraries(sandbox ${OPENGL_gl_LIBRARY})
target_link_libraries(sandbox ${GLUT_glut_LIBRARY_RELEASE})

