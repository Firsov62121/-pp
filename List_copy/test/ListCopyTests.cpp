#include <gtest/gtest.h>
#include "../listCopy.h"
#include "../myTestFuncs.h"

TEST(First, Correctness)
{
    for(int i = 1; i < 1000; ++i)
    {
        EXPECT_EQ(true, test(i, true));
    }
}