
###############################################################################
# Files
###############################################################################

file(GLOB HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h)
message("DD: ${HEADERS}")

install(FILES ${HEADERS} DESTINATION include/${PROJECT_NAME})
