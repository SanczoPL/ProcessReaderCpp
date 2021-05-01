cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

project(processreader VERSION 0.0.1 DESCRIPTION "processreader" LANGUAGES CXX)

find_package(Qt5Core REQUIRED)

enable_testing()
find_package(Threads REQUIRED)
macro(clone_build libname)
	configure_file(clone_build/${libname}.in ${libname}-download/CMakeLists.txt)
	execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
	WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/${libname}-download")
	execute_process(COMMAND "${CMAKE_COMMAND}" --build .
	WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/${libname}-download")
	add_subdirectory("${CMAKE_BINARY_DIR}/${libname}-src"
					"${CMAKE_BINARY_DIR}/${libname}-build")
endmacro()

clone_build(googletest)
# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

set(SRC_MAIN src/main.cc)

set(SRC
	src/processreader.cc
	src/queue.cc)

set(HEADERS
	include/processreader.h
	include/queue.h)

add_executable(g_test 
	${SRC} ${HEADERS}
	gtest/gtest.cc 
	gtest/gtest_queue.cc 
	gtest/gtest_queue.h)

add_executable(${PROJECT_NAME} ${SRC} ${HEADERS} ${SRC_MAIN})

target_link_libraries(${PROJECT_NAME} Qt5::Core)

target_link_libraries(g_test gtest gmock Qt5::Core)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 98)