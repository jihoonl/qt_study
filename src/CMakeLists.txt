

message("${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}")
#file(GLOB HEADERS RELATIVE ${PROJECT_SOURCE_DIR} include/${PROJECT_NAME}/ *.h)

qt5_wrap_cpp(MOC_SOURCES
  ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/glwidget.h
  ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/logo.h
  ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/mainwindow.h
  ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/window.h
)


include_directories(${CMAKE_CURRENT_BINARY_DIR})  # this is where ui headers are dropped.

file(GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

message("AA: ${SOURCES}")

message("AA : ${HEADERS}")

add_executable(qgl_viewer ${SOURCES} ${MOC_SOURCES})
qt5_use_modules(qgl_viewer Widgets OpenGL Gui Core)

target_link_libraries(qgl_viewer
  ${catkin_LIBRARIES}
  ${OPENGL_LIBRARIES}
  ${GLUT_LIBRARY}
)
