# Minimum version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(RelationalDBMS VERSION 1.0)

# Set C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

# Include directories for header files
include_directories(include)

# Add source files
file(GLOB SOURCES "src/*.c")

# Add library files (if you have any in the lib/ directory)
file(GLOB LIBRARIES "lib/*.a" "lib/*.so")

# Add the executable for the DBMS
add_executable(dbms ${SOURCES})

# Link the libraries (optional, if you have any libraries in lib/)
target_link_libraries(dbms ${LIBRARIES})

# Specify where the binary should be created
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Enable testing
enable_testing()

# Add tests from the tests/ directory
file(GLOB TEST_SOURCES "tests/*.c")
add_executable(dbms_test ${TEST_SOURCES})
add_test(NAME RunTests COMMAND dbms_test)

# Optional: Specify compiler flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")

# Set the output directory for libraries (if you are building them)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Set the C and C++ compilers
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
