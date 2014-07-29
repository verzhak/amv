
#
# Параметры сборки:
#
# CMAKE_BUILD_TYPE=Debug или CMAKE_BUILD_TYPE=Release (по умолчанию)
# WITH_OPENGL - поддержка OpenGL (через GLEW)
#

cmake_minimum_required(VERSION 2.8)

project(amv)

find_package(OpenCV REQUIRED)
find_package(OpenMP REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS} -Wall -pipe -std=gnu++11")
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
set(libraries ${OpenCV_LIBS})
add_definitions(-DIS_BUILD)

if(NOT CMAKE_BUILD_TYPE)

	set(CMAKE_BUILD_TYPE Debug)

endif()

set(sources base.cpp debug.cpp)

if(WITH_OPENGL)

	find_package(OpenGL REQUIRED)
	find_package(GLEW REQUIRED)

	include_directories(${GLEW_INCLUDE_DIRS})
	set(libraries ${libraries} ${OPENGL_gl_LIBRARY} ${GLEW_LIBRARY})

	add_definitions(-DWITH_OPENGL)

endif()

add_library(amv SHARED ${sources})
target_link_libraries(amv ${libraries})

############################################################################ 

configure_file(amv.pc.in amv.pc)

install(TARGETS amv LIBRARY DESTINATION lib)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include FILES_MATCHING PATTERN "*.hpp" PATTERN "build" EXCLUDE)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/amv.pc DESTINATION lib/pkgconfig)

