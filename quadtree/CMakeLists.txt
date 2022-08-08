cmake_minimum_required(VERSION 3.8.2) # 3.8.0 is minimum version that allow Linux remote building and debugging

# Remove trailing '\' and '/' at the end of the path, so can reliably compare
STRING(REGEX REPLACE "[/\\]+$" "" CMAKE_SOURCE_DIR ${CMAKE_SOURCE_DIR})
STRING(REGEX REPLACE "[/\\]+$" "" CMAKE_CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# When compiling DLib as stand alone library set to C++11,
# when library is part of other project, respect parent project settings.
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
	# Enforce c++11 standard.
	set (CMAKE_CXX_STANDARD 11)
endif()

# Notification when too low version of C++ is set
if(NOT DEFINED CMAKE_CXX_STANDARD OR CMAKE_CXX_STANDARD LESS 11)
	message(FATAL_ERROR "ERROR: CMAKE_CXX_STANDARD is not set or it is too low. Minimum C++ v11 is required to compile \"DLib\" library.")
endif()

   
set(MODULE_FILES
	quadtree/export.h
	quadtree/objects.h
	quadtree/quadtree.h
	objects.cpp
	quadtree.cpp
)


add_library(${DLIB} SHARED ${MODULE_FILES})


#include(GenerateExportHeader)
#generate_export_header(DLib)


# Make sure the compiler can find include files for our Hello library
# when other libraries or executables link to Hello
target_include_directories(${DLIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


# List files that install and/or package should provide.
# Each library should know what it want to distribute,
# which files are internal or intermediate and which are public library export.
install(TARGETS ${DLIB} DESTINATION DLib-bin)
install(FILES d-hello.h DESTINATION DLib-include)

add_custom_command(TARGET ${DLIB} POST_BUILD                        # Adds a post-build event
    COMMAND ${CMAKE_COMMAND} -E copy_if_different                   # which executes "cmake - E copy_if_different..."
        "${PROJECT_SOURCE_DIR}/bin/${DLIB}/Debug/${DLIB}.dll"       # <--this is in-file
        "${PROJECT_SOURCE_DIR}/bin/${APP}/${DLIB}.dll")             # <--this is out-file path
		

add_custom_command(TARGET ${DLIB} POST_BUILD                        # Adds a post-build event
    COMMAND ${CMAKE_COMMAND} -E copy_if_different                   # which executes "cmake - E copy_if_different..."
        "${PROJECT_SOURCE_DIR}/bin/${DLIB}/Debug/${DLIB}.dll"       # <--this is in-file
		"${PROJECT_SOURCE_DIR}/bin/${TEST_SUITE_NAME}/${DLIB}.dll")  # <--this is out-file path

message("${PROJECT_SOURCE_DIR}/bin/${TEST_SUITE_NAME}/${DLIB}.dll")