cmake_minimum_required(VERSION 3.2)
project(robocup_gamectrl)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

option(GC_CLIENT_BUILD_EXAMPLE "Build test binaty file" OFF)

find_package(Threads REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)

file(GLOB_RECURSE HDRS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")
file(GLOB_RECURSE SRCS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
                       "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

add_library(robocup_gamectrl STATIC ${SRCS} ${HDRS})
target_include_directories(robocup_gamectrl PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/")
target_link_libraries(robocup_gamectrl ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})

if (GC_CLIENT_BUILD_EXAMPLE)
    add_executable(example "${CMAKE_CURRENT_SOURCE_DIR}/example/main.cpp")
    target_link_libraries(example robocup_gamectrl)
endif()