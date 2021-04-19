cmake_minimum_required(VERSION 3.17)
project(crack)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "C:/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_definitions(-D_CRT_SECURE_NO_WARNINGS)

add_executable(crack)
target_sources(crack PUBLIC Main.cpp)
target_link_libraries(crack PUBLIC sfml-graphics sfml-audio)
