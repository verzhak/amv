
#
# Параметры сборки:
#
# CMAKE_BUILD_TYPE=Debug или CMAKE_BUILD_TYPE=Release (по умолчанию)
# CMAKE_TOOLCHAIN_FILE=~/trash/mips/mips.toolchain - сборка под MIPS
# WITH_OPENGL - поддержка OpenGL (через GLEW)
#

cmake_minimum_required(VERSION 3.0)
project(amv)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pipe -fPIC -std=c++11")
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
add_definitions(-DIS_BUILD)

if(NOT CMAKE_BUILD_TYPE)

	set(CMAKE_BUILD_TYPE Debug)

endif()

############################################################################ 

set(sources
	base/base.cpp
	debug/debug.cpp
	file/file.cpp
	#	image/bmp.cpp
	xml/xml.cpp
	)
set(libraries m)

add_library(amv SHARED ${sources})
target_link_libraries(amv ${libraries})
configure_file(amv.pc.in amv.pc)

add_executable(ex_1 example/ex_1.cpp)
target_link_libraries(ex_1 amv)

install(TARGETS amv LIBRARY DESTINATION lib)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include FILES_MATCHING PATTERN "*.hpp" PATTERN "build" EXCLUDE PATTERN ".git" EXCLUDE PATTERN "test" EXCLUDE PATTERN "trash" EXCLUDE PATTERN "doc" EXCLUDE PATTERN "example" EXCLUDE)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/amv.pc DESTINATION lib/pkgconfig)

