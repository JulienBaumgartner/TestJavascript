cmake_minimum_required(VERSION 3.14)

project(jsDuktape)

if(WIN32)
	add_compile_options("/std:c++latest")
	add_compile_options("/D _WIN32_WINNT=0x0601")
endif(WIN32)
set(CMAKE_CXX_STANDARD 17)
enable_testing()

find_package(duktape CONFIG REQUIRED)
find_package(Gtest CONFIG REQUIRED)

include_directories(${CMAKE_CURRENT_SOURC_DIR} ${DUKTAPE_INCLUDE_DIRS})

add_library(javascript_lib
	${CMAKE_CURRENT_SOURCE_DIR}/javascript/javascript.h
	${CMAKE_CURRENT_SOURCE_DIR}/javascript/javascript.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/javascript/js_duktape.h
	${CMAKE_CURRENT_SOURCE_DIR}/javascript/js_duktape.cpp
)

target_link_libraries(javascript_lib
  PRIVATE
	${DUKTAPE_LIBRARY}
)

add_executable(test_cmd
	${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/javascript_test.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/javascript_test.cpp
)

target_link_libraries(test_cmd
  PRIVATE
	GTest::gtest
	GTest::gtest_main
	GTest::gmock
	GTest::gmock_main
	javascript_lib
	${DUKTAPE_LIBRARY}
)