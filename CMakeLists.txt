cmake_minimum_required(VERSION 3.8.2) # 3.8.0 is minimum version that allow Linux remote building and debugging
project(quadtree)

set(DLIB quadtree)
set(APP quadtree_gui)
set(TEST_SUITE_NAME quadtree_tests)

# Enforce c++11 standard.
set (CMAKE_CXX_STANDARD 11)


# The version number.
set(Example_VERSION_MAJOR 2)
set(Example_VERSION_MINOR 3)
set(Example_VERSION_PATCH 1)


# This project consist of 3 components, each in one directory, so add each of them
add_subdirectory(quadtree)
add_subdirectory(quadtree_tests)
add_subdirectory(quadtree_gui)


# USE_FOLDERS group cmake generated projects into one (CMakePredefinedTargets) folder
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Below line set Demo as startup application in Visual Studio
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT quadtree_gui)

