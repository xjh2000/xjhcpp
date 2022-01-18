add_library(baseStruct Vector.h Vector_util.h main.cpp ListNode.h List.h)

target_include_directories(baseStruct
        INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
        )