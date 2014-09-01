
project(amv_test)

add_executable(amv_test main.cpp)
target_link_libraries(amv_test amv ${OpenCV_LIBS})

