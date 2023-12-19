cmake_minimum_required(VERSION 3.20)
project(akai_app VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(external/akai_engine)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} akai_engine)
target_include_directories(${PROJECT_NAME} PRIVATE akai_engine)