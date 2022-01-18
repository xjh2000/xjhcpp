include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(test  BaseTest.cpp VectorTest.cpp ListTest.cpp)

target_link_libraries(test gtest_main)
target_link_libraries(test my_utils baseStruct)

include(GoogleTest)
gtest_discover_tests(test)