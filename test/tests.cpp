#include "gtest/gtest.h"

#include "../src/func.h"

TEST(HelloWorldTests, test1) {
    EXPECT_TRUE(true);
    std::string result = GetHelloWorld(5);
    EXPECT_EQ(result, "Hello, World!")
            << "Strings do not match";
}
