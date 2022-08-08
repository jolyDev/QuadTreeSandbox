# Pass information about version to C++ code through header
#    that will be supplemented by cmake.
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/version.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/version.h"
)

# version.h file is in output directory.
# Add the binary tree directory to find the version.h file
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(${APP} main.cpp version.h)


target_link_libraries(${APP}
	${DLIB}
)

install(TARGETS ${APP} DESTINATION ${APP})

