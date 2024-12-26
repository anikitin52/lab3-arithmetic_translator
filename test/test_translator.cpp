#include <gtest.h>
#include "ArithmeticExpression.h"

TEST(Expression, SimpleADD) {
    Expression expr("1+2");
    
    ASSERT_EQ(expr.Calculate(), 3);
}

TEST(Expression, SimpleSub) {
    Expression expr("1-2");

    ASSERT_EQ(expr.Calculate(), 0);
}
