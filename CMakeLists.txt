cmake_minimum_required(VERSION 3.2)

project(game)
include_directories("/usr/local/include")
include_directories("/usr/local/include/opencv4")
find_package( OpenCV REQUIRED )

add_executable(game test/connect.cc helpers/glad.c helpers/objloader.cpp helpers/chesstype.cc helpers/chesspiece.cc 
               connection.cc server.cc)
               
install(TARGETS game RUNTIME DESTINATION bin)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread -g")
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(game Threads::Threads)

target_link_libraries(game ${OpenCV_LIBS} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

target_link_libraries(game
    glfw
    glut
    GL
    dl
)

find_package(glfw3 3.3 REQUIRED)
target_link_libraries(game glfw)

include_directories(${SOURCE_FILES})
