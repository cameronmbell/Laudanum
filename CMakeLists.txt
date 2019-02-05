# create project
cmake_minimum_required(VERSION 3.0)
project(laudanum)

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
    ${HDR_DIR}/laudanum/FStandard.hpp
    ${HDR_DIR}/laudanum/FExcept.hpp
    ${HDR_DIR}/laudanum/FInputListener.hpp
    ${HDR_DIR}/laudanum/FShader.hpp
    ${HDR_DIR}/laudanum/FWindow.hpp

    ${HDR_DIR}/laudanum/Shader.hpp
)
# actually build
add_executable(${PROJECT_NAME} ${SOURCES})

# set warning level to maximum
if ( CMAKE_COMPILER_IS_GNUCC )
  target_compile_options(${PROJECT_NAME} PRIVATE "-Wall")
endif()
if ( MSVC )
  target_compile_options(${PROJECT_NAME} PRIVATE "/W4")
endif()

# get OpenGL + GLFW deps
set(DEPENDENCIES_ROOT "${CMAKE_SOURCE_DIR}/3rd_party")

IF(UNIX)
  target_include_directories(${PROJECT_NAME} PUBLIC ${HDR_DIR})

  # use c++11 standard
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)

  # GLFW
  set(GLFW_DIR "${DEPENDENCIES_ROOT}/lib")
  set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
  set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
  set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
  set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
  add_subdirectory("${GLFW_DIR}")
  target_link_libraries(${PROJECT_NAME} "glfw" "${GLFW_LIBRARIES}")
  target_include_directories(${PROJECT_NAME} PRIVATE "${GLFW_DIR}/include")
  target_compile_definitions(${PROJECT_NAME} PRIVATE "GLFW_INCLUDE_NONE")
ENDIF()

IF(WIN32)
  set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/3rd_party/modules/")


  find_package(OpenGL REQUIRED)
  find_package(glfw3 REQUIRED)

  message("GLFW3 lib directory is: ${GLFW3_LIBRARY}")
  message("GLFW3 include directory is: ${GLFW3_INCLUDE_DIR}")


  message(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLFW3_LIBRARY})

  # link against deps
  target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLFW3_LIBRARY})
  target_include_directories(${PROJECT_NAME} PUBLIC
    ${OPENGL_INCLUDE_DIR}
    ${GLFW3_INCLUDE_DIR}
  ${HDR_DIR})
ENDIF()

# compile GLAD
add_library("glad" ${DEPENDENCIES_ROOT}/src/glad.c)

target_include_directories("glad" PRIVATE ${DEPENDENCIES_ROOT}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${DEPENDENCIES_ROOT}/include)
target_link_libraries(${PROJECT_NAME} "glad" "${CMAKE_DL_LIBS}")

  # use c++11 standard
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)

  # copy resources
  # set (RES_DIR "${CMAKE_SOURCE_DIR}/res")
  # set (RES_DEST "${CMAKE_CURRENT_BINARY_DIR}/res")
  # add_custom_command(
  #     TARGET ${PROJECT_NAME} POST_BUILD
  #     COMMAND ${CMAKE_COMMAND} -E create_symlink ${RES_DIR} ${RES_DEST}
  #     DEPENDS ${RES_DEST}
  #     COMMENT "symbolic link resources folder from ${RES_DIR} => ${RES_DEST}"
# )

add_custom_command(
  TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)
