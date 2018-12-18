cmake_minimum_required(VERSION 3.7)
project(crumpet-engine)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} CMakeFiles/)
cmake_policy(SET CMP0037 OLD)
set(CMAKE_BUILD_TYPE Debug)

set(BuildDir ./bin)
set(BuildExecutable resource-monitor)
set(Build ${BuildDir}/${BuildExecutable})

set(SourceDir ./src)
set(LibSysSource ./libsys)

set(Include ./include)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

include_directories(${Build} ${Include}/)

file(GLOB_RECURSE LibSys
    ${LibSysSource}/*.cpp
)

file(GLOB_RECURSE SourceFiles
    ${SourceDir}/*.cpp
)

add_executable(${Build} 
    ${LibSys}
    ${SourceFiles}
)

target_link_libraries(${Build} Threads::Threads)
