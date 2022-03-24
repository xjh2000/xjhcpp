add_subdirectory(utils)

add_library(baseStruct Vector/Vector.h Vector/Vector_util.h main.cpp List/ListNode.h List/List.h BinTree/BinNode.h BinTree/BinTree.h Graph/Graph.h Graph/GraphMatrix.h Entry/Entry.h BST/BST.h BST/AVL.h BST/Splay.h BTree/BTNode.h BTree/BTree.h BST/RedBlack.h Dictionary/Dictionary.h Dictionary/SkipList.h Dictionary/Quadlist.h Dictionary/QuadlistNode.h PQ/PQ.h PQ/PQ_ComplHeap.h)

target_include_directories(baseStruct
        INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
        )

add_subdirectory(gtest)