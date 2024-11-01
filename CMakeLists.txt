cmake_minimum_required(VERSION 3.15)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(
  Text_Editor
  VERSION 0.0.1
  LANGUAGES CXX C
)
find_package(Git)
# TODO: Add error handling incase anything goes wrong while trying to update
if(GIT_FOUND)
  message(STATUS "Downloading submodules")
  if(NOT EXISTS ${CMAKE_SOURCE_DIR}/include/libraries/cpp-terminal)
    execute_process(COMMAND mkdir -p include/libraries
                    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
    execute_process(COMMAND ${GIT_EXECUTABLE} submodule add https://github.com/jupyter-xeus/cpp-terminal
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/include/libraries
    )
  else()
      message(STATUS "Submodule update")
      execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/include/libraries/cpp-terminal
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
      if(NOT GIT_SUBMOD_RESULT EQUAL "0")
        message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
      endif()
  endif()
else()
  message(FATAL_ERROR "Git not installed. Please install to compile the program")
endif()

set (CMAKE_CXX_STANDARD 23)
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW) # allow to override variables within the CMakeLists.txt of the library
set(CPPTERMINAL_BUILD_EXAMPLES OFF) # disable building examples
set(CPPTERMINAL_ENABLE_INSTALL OFF) # disable the installation of the library
set(CPPTERMINAL_ENABLE_TESTING ON) # disable the tests of the library ... when running 'ctest' we only want to see our own tests
add_subdirectory("./include/libraries/cpp-terminal")

set( SOURCE_PATH "${PROJECT_SOURCE_DIR}/src" )
set( INCLUDE_PATH "${PROJECT_SOURCE_DIR}/include" )


file( GLOB_RECURSE headers "${INCLUDE_PATH}/*.hpp" )
file( GLOB_RECURSE src "${SOURCE_PATH}/*.cpp" )

add_executable(Text_Editor ${headers} ${src})
target_link_libraries(Text_Editor PUBLIC 
                      cpp-terminal)
