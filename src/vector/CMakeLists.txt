add_library(vector Vector.h vector_implementation.h Vector.cpp)

target_include_directories(vector
        INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
        )