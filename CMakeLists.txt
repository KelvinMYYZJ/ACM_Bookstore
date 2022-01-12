cmake_minimum_required(VERSION 3.16)
project(Bookstore)

set(CMAKE_CXX_STANDARD 20)
if (LOCALTEST)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/runtime)
	add_compile_options(-std=c++2a -g)
else()
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
	add_compile_options(-std=c++2a -o2)
	add_definitions(-DONLINE_JUDGE)
endif()
include_directories(
        ${PROJECT_SOURCE_DIR}/src/
        ${PROJECT_SOURCE_DIR}/src/FileSystem/
        ${PROJECT_SOURCE_DIR}/src/BookStore/
        ${PROJECT_SOURCE_DIR}/bin/
)
file(GLOB_RECURSE BookStore_SRCS "src/BookStore/*.cpp")
file(GLOB_RECURSE FileSystem_SRCS "src/FileSystem/*.cpp")
list(APPEND lib_dir ${BookStore_SRCS})
#list(REMOVE_ITEM lib_dir ${PROJECT_SOURCE_DIR}/src/BookStore/BookStore.cpp)
list(APPEND lib_dir ${FileSystem_SRCS})
message("arg1 = ${lib_dir}")  
set(src_dir
        ${PROJECT_SOURCE_DIR}/src/main_stdio.cpp
        )
set(test_main_dir
        ${PROJECT_SOURCE_DIR}/src/main.cpp
)
set(test_dir
        ${PROJECT_SOURCE_DIR}/src/test/test.cpp


)
add_executable(code ${src_dir} ${lib_dir})
if (LOCALTEST)
	add_executable(test ${test_main_dir} ${lib_dir} )
	add_executable(temp ${test_dir} ${lib_dir} )
endif()