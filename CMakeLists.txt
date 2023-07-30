cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

set(This BinaryTreeProject)
set(SOURCE_NAME main)
project(${This})

enable_testing()
add_subdirectory(googletest)
add_subdirectory(tests)
add_subdirectory(src)

add_executable(${SOURCE_NAME} ${SOURCE_NAME}.cpp)
target_link_libraries(${SOURCE_NAME} PRIVATE BinaryTree)