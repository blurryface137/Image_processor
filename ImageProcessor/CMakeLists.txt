cmake_minimum_required (VERSION 2.6)

project(ImageProcessor)

include_directories(${PROJECT_SOURCE_DIR}/src)
file(GLOB SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)
set(SOURCES 
	${CMAKE_CURRENT_SOURCE_DIR}/src/Bitmap.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Filter.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Handler.cpp)
add_executable(image_processor src/ImageProcessor.cpp ${SOURCES})

add_subdirectory(tests)