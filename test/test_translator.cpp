#include <gtest.h>
#include "ArithmeticExpression.h"

TEST(Expression, CanCreateExpression) {
	ASSERT_NO_THROW(Expression expr("2+2*2"));
}