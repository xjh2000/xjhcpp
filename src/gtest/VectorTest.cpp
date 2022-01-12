//
// Created by 93462 on 1/12/2022.
//

#include "gtest/gtest.h"
#include "Vector.h"


namespace {

    class VectorTest : public testing::Test {
    };

    TEST_F(VectorTest,initialized){
        Vector<int> v;
        printf("ok");
    }

}
