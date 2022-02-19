add_subdirectory(utils)

add_library(baseStruct Vector/Vector.h Vector/Vector_util.h main.cpp List/ListNode.h List/List.h BinTree/BinNode.h BinTree/BinTree.h Graph/Graph.h Graph/GraphMatrix.h Entry/Entry.h BST/BST.h)

target_include_directories(baseStruct
        INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
        )

add_subdirectory(gtest)