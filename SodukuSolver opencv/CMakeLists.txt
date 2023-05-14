cmake_minimum_required(VERSION 3.12)
project(WebcamBasedSudokuSolverViaOpenCV)

# Find OpenCV package
find_package(OpenCV REQUIRED)

# Add your header files
include_directories(include)

# Add your source files
add_executable(app main.cpp)

# Link your executable against the OpenCV library
target_link_libraries(app PRIVATE ${OpenCV_LIBS})
