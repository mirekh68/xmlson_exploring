cmake_minimum_required(VERSION 3.14)

project(xmlson)

add_compile_options(-std=c++17 -frecord-gcc-switches)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

conan_basic_setup(TARGETS)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} CONAN_PKG::rapidxml CONAN_PKG::rapidjson CONAN_PKG::nlohmann_json)


