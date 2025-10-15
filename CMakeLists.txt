cmake_minimum_required(VERSION 3.24)
project(assignment05-solved)

set(CMAKE_CXX_STANDARD 20)


link_libraries(cs4722  glfw3 opengl32 glu32)

include_directories(C:/cs4722lib/include cs4722lib/include)
link_directories(C:/cs4722lib cs4722lib)

configure_file(fragment_shader.glsl .)
configure_file(vertex_shader.glsl .)

add_executable(base base/main.cpp)
add_executable(step1 step1/main.cpp)
add_executable(step2 step2/main.cpp)
add_executable(step3 step3/main.cpp)
add_executable(step4 step4/main.cpp)



