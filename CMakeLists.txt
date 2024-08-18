cmake_minimum_required(VERSION 3.10)
project(String_Compare_Goods)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

#set(CMAKE_SYSTEM_NAME Linux)
#set(CMAKE_SYSTEM_PROCESSOR x86_64)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")


# if(${CMAKE_VERSION} VERSION_GREATER_EQUAL 3.30)
#   cmake_policy(SET CMP0167 NEW)
# endif()
# find_package(Boost)
# if(Boost_FOUND)
#   include_directories(${Boost_INCLUDE_DIRS})
#   add_executable(example example.cpp soft_string_compare/soft_string_compare.cpp)
#   target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
# endif()

add_executable(example example.cpp soft_string_compare/soft_string_compare.cpp)


# Emscripten-specific settings
if(EMSCRIPTEN)
  set(CMAKE_EXECUTABLE_SUFFIX ".js")
  set_target_properties(example PROPERTIES LINK_FLAGS "-s WASM=1 -s NO_EXIT_RUNTIME -s EXPORTED_RUNTIME_METHODS=['ccall','cwrap'] -s ALLOW_MEMORY_GROWTH=1 -s MODULARIZE=1 --shell-file /usr/lib/emscripten/src/shell_minimal.html")
endif()
