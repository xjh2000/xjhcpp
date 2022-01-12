add_library(vector Vector.h Vector.cpp)

target_include_directories(vector
        INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
        )