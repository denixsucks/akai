cmake_minimum_required(VERSION 3.5)
project(akai_engine VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(external/glm)
add_subdirectory(external/glfw)
add_subdirectory(external/vk-bootstrap)
# add_subdirectory(external/imgui)

find_package(vulkan REQUIRED)

file(GLOB SOURCES "src/*.cpp", "src/*/*.cpp", "src/*/*/*.cpp") # dont forget to add another layer if you go deep.

add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    glm
    # imgui
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${Vulkan_INCLUDE_DIRS}
    glfw
    vk-bootstrap

)

target_link_libraries(${PROJECT_NAME}
  PUBLIC
    # imgui
    glm
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${Vulkan_LIBARIES}
    glfw
    vk-bootstrap
)