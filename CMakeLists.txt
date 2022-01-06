cmake_minimum_required(VERSION 3.16)
project(Bookstore)

set(CMAKE_CXX_STANDARD 20)
set(ONLINEJUDGE 1)
if (ONLINEJUDGE)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
	add_compile_options(-std=c++2a -o2)
	add_definitions(-DONLINE_JUDGE)
else()
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/runtime)
	add_compile_options(-std=c++2a -g)
endif()
include_directories(
        ${PROJECT_SOURCE_DIR}/src/
        ${PROJECT_SOURCE_DIR}/bin/
)
set(src_dir
        ${PROJECT_SOURCE_DIR}/src/main.cpp
        )
set(lib_dir
        ${PROJECT_SOURCE_DIR}/src/MyString.cpp
				)
set(test_dir
        ${PROJECT_SOURCE_DIR}/src/test/test.cpp
)
set(running_dir
				${PROJECT_SOURCE_DIR}/running
)
#add_executable(code ${src_dir})
add_executable(code ${test_dir} ${lib_dir} )

# 添加链接库
#target_link_libraries(code ${PROJECT_SOURCE_DIR}/bin/libUll.a)

# 后缀名为 .a 和 .so 的文件分别为静态链接库和动态链接库