
#
# Параметры сборки:
#
# CMAKE_BUILD_TYPE=Debug или CMAKE_BUILD_TYPE=Release (по умолчанию)
# CMAKE_TOOLCHAIN_FILE=~/trash/mips/mips.toolchain - сборка под MIPS
# WITH_OPENGL - поддержка OpenGL (через GLEW)
#

cmake_minimum_required(VERSION 3.0)

project(amv)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pipe -fPIC -std=gnu++11 -Wno-poison-system-directories")
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
add_definitions(-DIS_BUILD)

set(sources base.cpp debug.cpp xml/xml.cpp image/bmp.cpp file/file.cpp)
set(libraries m)

if(NOT CMAKE_BUILD_TYPE)

	set(CMAKE_BUILD_TYPE Debug)

endif()

############################################################################ 
# Platform specific

if(${MIPS})

else()

	find_package(OpenCV REQUIRED)

	set(sources ${sources} image/contours/morph.cpp)
	set(libraries ${libraries} ${OpenCV_LIBS})

	if(WITH_OPENGL)

		find_package(OpenGL REQUIRED)
		find_package(GLEW REQUIRED)

		include_directories(${GLEW_INCLUDE_DIRS})
		add_definitions(-DWITH_OPENGL)

		set(libraries ${libraries} ${OPENGL_gl_LIBRARY} ${GLEW_LIBRARY})

	endif()

	add_subdirectory(test)

endif()

############################################################################ 

add_library(amv SHARED ${sources})
target_link_libraries(amv ${libraries})
configure_file(amv.pc.in amv.pc)

install(TARGETS amv LIBRARY DESTINATION lib)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include FILES_MATCHING PATTERN "*.hpp" PATTERN "build" EXCLUDE PATTERN ".git" EXCLUDE PATTERN "test" EXCLUDE)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/amv.pc DESTINATION lib/pkgconfig)

