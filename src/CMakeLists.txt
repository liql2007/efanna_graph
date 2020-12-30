set(CMAKE_CXX_STANDARD 11)

file(GLOB_RECURSE CPP_SOURCES *.cpp)

list(FILTER CPP_SOURCES EXCLUDE REGEX ".*/index_pq.cpp$")

add_library(${PROJECT_NAME} ${CPP_SOURCES})
add_library(${PROJECT_NAME}_s STATIC ${CPP_SOURCES})

#install()