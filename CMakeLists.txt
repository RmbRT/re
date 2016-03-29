cmake_minimum_required(VERSION 2.6)
project(RmbRT_Engine)

# Set the C++ standard used by the RmbRT Engine.
set(CMAKE_CXX_FLAGS "-std=c++11")

# Add Lock library include path.
include_directories(depend/Lock/include);

# Select all source files.
file(GLOB_RECURSE re_sources ./src/*.cpp)
# Add them to the RmbRT Engine library.
add_library(re ${re_sources})

# Add GLFW to the build chain.
add_subdirectory(depend/glfw)
# Set up the GLFW include directory.
include_directories(depend/glfw/include)
# Link the RmbRT Engine with GLFW.
target_link_libraries(re glfw ${GLFW_LIBRARIES})

# Creates an include directory containing all header files used in the RmbRT Engine.
# Add /re/include/ to your include directories and access the files via #include <re/*>
file(COPY "src/" DESTINATION "include/re/" FILES_MATCHING PATTERN "*.hpp" PATTERN "*.inl")