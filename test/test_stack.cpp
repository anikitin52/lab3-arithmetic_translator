#include <gtest.h>
#include <vector>
#include "stack.h"

TEST(Stack, CanCreateStack) {
	ASSERT_NO_THROW(Stack<int> st1);
}
TEST(Stack, CanPushBack) {
	Stack<int> st1;
	st1.push(1);
	ASSERT_EQ(st1.top(), 1);
}
TEST(Stack, CanPopBack) {
	Stack<int> st1;
	st1.push(1);
	st1.push(2);
	st1.pop();
	ASSERT_EQ(st1.top(), 1);
}
TEST(Stack, CantPopBackFormEmptyStack) {
	Stack<int> st1;
	ASSERT_ANY_THROW(st1.pop());
}
TEST(Stack, CanGetTopElement) {
	Stack<int> st1;
	st1.push(1);
	st1.push(2);
	ASSERT_EQ(st1.top(), 2);
}
TEST(Stack, CantGetTopElementFromEmptyStack) {
	Stack<int> st1;
	ASSERT_ANY_THROW(st1.top());
}
TEST(Stack, EmptyCheckTrue) {
	Stack<int> st1;
	ASSERT_EQ(st1.empty(), true);
}
TEST(Stack, EmptyCheckFalse) {
	Stack<int> st1;
	st1.push(1);
	ASSERT_EQ(st1.empty(), false);
}
TEST(Stack, CanGetSize) {
	Stack<int> st1;
	st1.push(1);
	st1.push(1);
	st1.push(1);
	st1.push(1);
	st1.push(1);
	ASSERT_EQ(st1.size(), 5);
	st1.push(1);
}