cmake_minimum_required(VERSION 3.2)
project(${TEST_SUITE_NAME})

#Set up gtest
include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(${DIVISION_HEADERS_DIR})
include_directories(lib/googletest/googletest/include)

set(SOURCE_FILES main.cpp tests.cpp)

add_executable(${TEST_SUITE_NAME} ${SOURCE_FILES})
target_link_libraries(${TEST_SUITE_NAME} gtest)
install(TARGETS ${TEST_SUITE_NAME} DESTINATION bin)


target_link_libraries(${TEST_SUITE_NAME}
	${DLIB}
)

install(TARGETS ${TEST_SUITE_NAME} DESTINATION ${TEST_SUITE_NAME})
