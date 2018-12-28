# create project
cmake_minimum_required(VERSION 3.0)
project(laudanum)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/3rd_party/modules/")

# dirs + sources
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(HDR_DIR "${CMAKE_SOURCE_DIR}/include")
set(SOURCES
    ${SRC_DIR}/FExcept.cpp
    ${SRC_DIR}/FInputListener.cpp
    ${SRC_DIR}/FShader.cpp
    ${SRC_DIR}/FWindow.cpp
    ${SRC_DIR}/main.cpp
    ${HDR_DIR}/laudanum/FDefines.hpp
    ${HDR_DIR}/laudanum/FExcept.hpp
    ${HDR_DIR}/laudanum/FInputListener.hpp
    ${HDR_DIR}/laudanum/FShader.hpp
    ${HDR_DIR}/laudanum/FWindow.hpp
)

# get OpenGL + GLFW deps
set(DEPENDENCIES_ROOT "${CMAKE_SOURCE_DIR}/3rd_party")

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

message("GLFW3 lib directory is: ${GLFW3_LIBRARY}")
message("GLFW3 include directory is: ${GLFW3_INCLUDE_DIR}")

# actually build
add_executable(${PROJECT_NAME} ${SOURCES})

message(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLFW3_LIBRARY})

# set warning level to maximum
if ( CMAKE_COMPILER_IS_GNUCC )
    target_compile_options(${PROJECT_NAME} PRIVATE "-Wall")
endif()
if ( MSVC )
    target_compile_options(${PROJECT_NAME} PRIVATE "/W4")
endif()

# compile GLAD
add_library("glad" ${DEPENDENCIES_ROOT}/src/glad.c)

target_include_directories("glad" PRIVATE ${DEPENDENCIES_ROOT}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${DEPENDENCIES_ROOT}/include)
target_link_libraries(${PROJECT_NAME} "glad" "${CMAKE_DL_LIBS}")

# link against deps
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLFW3_LIBRARY})
target_include_directories(${PROJECT_NAME} PUBLIC 
    ${OPENGL_INCLUDE_DIR}
    ${GLFW3_INCLUDE_DIR}
    ${HDR_DIR})

# use c++11 standard
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)