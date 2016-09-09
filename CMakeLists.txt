cmake_minimum_required(VERSION 2.8.3)
project(rgbd_viewer)

find_package(catkin REQUIRED)

find_package(Qt5Widgets)
find_package(Qt5OpenGL)
find_package(Qt5Core)
find_package(Qt5Gui)

# OpenGL
FIND_PACKAGE(OpenGL REQUIRED)
if(NOT OPENGL_FOUND)
  message(ERROR " OPENGL not found!")
else()
  message(STATUS " OPENGL found!")
endif(NOT OPENGL_FOUND)

include_directories(
  include
)


catkin_package(
  DEPENDS GLUT OpenGL QT
)

add_subdirectory(include)
add_subdirectory(src)
