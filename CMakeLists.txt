
# SETUP
cmake_minimum_required(VERSION 3.12)
project(main)

set(VULKAN_SDK_PATH "/home/javi/Vulkan/1.3.211.0/x86_64/")
set(Vulkan_INCLUDE_DIRS "${VULKAN_SDK_PATH/include}")
set(Vulkan_LIBRARIES "${VULKAN_SDK_PATH/lib}")

find_package(Vulkan REQUIRED)

#set(OPT_FLAGS
#    "-Ofast -mtune=native -floop-parallelize-all -fgcse-sm"
#)


# Directories containing headers must be specified in the include_directories()
include_directories(
    "src"
    "includes"
)

# Searches for all .cc files
file(GLOB_RECURSE SRC "src/*.cc")

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OPT_FLAGS} -g -Wall -Wextra")#Werror

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g3")# -fsanitize=address")

add_executable(main)
target_sources(main PRIVATE "src/engine.cc" ${SRC})
target_link_libraries(main ${Vulkan_LIBRARIES})