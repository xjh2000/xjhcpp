add_library(my_utils Hello.cpp Hello.h)

target_include_directories(my_utils
        INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
        )