cmake_minimum_required(VERSION 3.7)
project(crumpet-engine)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} CMakeFiles/)
cmake_policy(SET CMP0037 OLD)

set(BuildDir ./bin)
set(BuildExecutable resource-monitor)
set(Build ${BuildDir}/${BuildExecutable})

set(SourceDir ./src)
set(Platform ./platform)
set(WinDep ${Platform}/win32)
set(LinuxDep ${Platform}/linux)

set(Include ./include)

find_package(Threads REQUIRED)

include_directories(${Build}/ ${Include})

if (WIN32)
    file(GLOB_RECURSE PlatformDepSource
        ${WinDep}/monitoring/*.cpp
        ${WinDep}/ui/*.cpp
    )
endif (WIN32)

if (UNIX)
    file(GLOB_RECURSE PlatformDepSource
        ${LinuxDep}/monitoring/*.cpp
        ${LinuxDep}/ui/*.cpp
    )
endif (UNIX)

file(GLOB_RECURSE SourceFiles
    ${SourceDir}/*.cpp
)

add_executable(${Build} 
    ${SourceFiles}
    ${PlatformDepSource}
)

target_link_libraries(${Build} Threads::Threads)
