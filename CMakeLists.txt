cmake_minimum_required(VERSION 3.0)
project(BinPacking3DM2)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Bin")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread -fpermissive")

file(GLOB_RECURSE SOURCE_FILES
        ${CMAKE_SOURCE_DIR}/Src/*.c
        ${CMAKE_SOURCE_DIR}/Src/*.cpp
        )

file(GLOB_RECURSE HEADER_FILES
        ${CMAKE_SOURCE_DIR}/Include
        ${CMAKE_SOURCE_DIR}/Include)

file(GLOB LIB_DIR
        Lib
        )

include_directories(${HEADER_FILES})

include_directories(
        "${CMAKE_SOURCE_DIR}/Src"
        "${CMAKE_SOURCE_DIR}/Include"
)

set(LIBS OpenGL glut GLU)

link_directories(${LIB_DIR})

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${LIBS})
