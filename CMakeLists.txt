
# SETUP
cmake_minimum_required(VERSION 3.12)
    project(main)

#set(OPT_FLAGS
#    "-Ofast -mtune=native -floop-parallelize-all -fgcse-sm"
#)

# Directories containing headers must be specified in the include_directories()
include_directories(
    "src"
    "C:/VulkanSDK/1.3.236.0/Include"
    "C:/glfw/include"
)

link_directories(
    "C:/VulkanSDK/1.3.236.0/Lib"
    "C:/glfw/lib"
    )

# Searches for all .cc files
file(GLOB_RECURSE SRC "src/*.cc")

set(CMAKE_CXX_STANDARD 17)

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OPT_FLAGS} -g -Wall -Wextra")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g3")
endif(CMAKE_COMPILER_IS_GNUCXX)

add_executable(main)
target_sources(main PRIVATE "src/engine.cc" ${SRC})
target_link_libraries(main ${Vulkan_LIBRARIES} glfw3)