cmake_minimum_required(VERSION 2.8)

project(Asterisk)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

file(GLOB SRC "*.c")
add_executable(Asterisk ${SRC})

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED network audio graphics window system)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(Asterisk ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

file(COPY res DESTINATION ${PROJECT_BINARY_DIR})
