// тесты для вычисления арифметических выражений


#include "arithmetic.h"
#include <gtest.h>
TEST(Arithmetic, can_create_expression)
{
	ASSERT_NO_THROW(Arithmetic x("a+b"));
}


TEST(Arithmetic, cant_start_infix_with_operation)
{
	Arithmetic x("+a+b");
	EXPECT_EQ(false, x.Error());
}

TEST(Arithmetic, cant_end_infix_with_operation)
{
	Arithmetic x("a+b+");
	EXPECT_EQ(false, x.Error());
}


TEST(Arithmetic, cant_count_expression_with_wrong_symbols)
{
	Arithmetic x("5.7%+(4*7-8.5)");
	EXPECT_EQ(false, x.Error());
}



TEST(Arithmetic, can_create_right_expression)
{
	Arithmetic x("(a+b)");
	EXPECT_EQ("a,b,+,", x.ToPostfix());
}

TEST(Arithmetic, can_calculate_expression)
{
	Arithmetic x("(1+2)+3*4");
	x.ToPostfix();
	EXPECT_EQ(15, x.Calculator());
}

TEST(Arithmetic, can_calculate_expression_with_variables)
{
	Arithmetic x("(a+b)+c*d");
	cout << "enter a=4,b=4,c=2,d=4" << endl;
	x.ToPostfix();
	EXPECT_EQ(16, x.Calculator());
}

TEST(Arithmetic, can_get_right_priority_of_the_operations)
{
	Arithmetic x("a+b*c");
	EXPECT_TRUE(x.Priority('*', '+') == 1);
}
