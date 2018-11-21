// объ€вление функций и классов дл€ вычислени€ арифметических выражений
#ifndef _ARITHMETIC_H_ 
#define _ARITHMETIC_H_ 

#include <iostream>
#include <string>
#include<vector>
#include "stack.h"
using namespace std;


class Arithmetic
{
	string infix;
	string postfix;

public:
	Arithmetic(string s)
	{
		infix = s;
	}


	bool IsOperator(char s)
	{
		
		if (s == '+' || s == '*' || s == '-' || s == '/')
			return true;
		else return false;
	}
	int Priority(char s1, char s2)
	{
		if ((s1 == '*' || s1 == '/') && (s2 == '+' || s2 == '-'))
			return 1;
		if ((s1 == '+' || s1 == '-') && (s2 == '+' || s2 == '-'))
			return 0;
		if ((s1 == '*' || s1 == '/') && (s2 == '*' || s2 == '/'))
			return 0;
		if ((s1 == '+' || s1 == '-') && (s2 == '*' || s2 == '/'))
			return -1;
	}

	
	string ToPostfix()
	{
		Stack<char> opers(infix.size());
		string tmp;
		for (int i = 0; i < infix.size(); i++)
		{
			if (!IsOperator(infix[i])) 
				postfix += infix[i];
			
			else
				if (opers.IsEmpty() || opers.CheckTopEl() == '(')
					opers.Push(infix[i]);
				else
					if (Priority(infix[i], opers.CheckTopEl()) == 1)
						opers.Push(infix[i]);
					else
						if (Priority(infix[i], opers.CheckTopEl()) <= 0)
						{
							while ((!opers.IsEmpty()) && (opers.CheckTopEl() != '(' || Priority(opers.CheckTopEl(), infix[i]) != -1))
							{
								postfix += opers.Pop();
							}
							opers.Push(infix[i]);
						}
						else
							if (infix[i] == '(')
								opers.Push(infix[i]);
							else
								if (infix[i] == ')')
								{
									while (opers.CheckTopEl() != '(')
										postfix += opers.Pop();
									opers.Pop();
								}



		}
		while (!opers.IsEmpty())
			postfix += opers.Pop();
		return postfix;
	}

	double count(double a, double b, char c)
	{
		double res;
		if (c == '+')
			res = a + b;
		if (c == '-')
			res = a - b;
		if (c == '*')
			res = a * b;
		if (c == '/')
		{
			if (b == 0) throw "impossible to divide by zero";
		}
				res = a / b;
		return res;
	}

	void Input(string s)
	{
		string tmp;
		for (int i = 0; i < s.size(); i++)
		{
			if ((int(s[i]) >= 65 && int(s[i]) <= 90) || (int(s[i]) >= 97 && int(s[i]) <= 122)) //значени€ переменных в диапазоне
			{
				cout << "¬ведите переменную " << s[i] << ':';
				cin >> tmp;
			}
		}
	}

	string NewInfix() 
	{
		string news,tmp;
		for (int i = 0; i < infix.size(); i++)
		{
			if (isdigit(infix[i]) == 0)
			{
				news += infix[i];
			}
			else
			{
				while (infix[i] != ')' && infix[i] != '(' && !IsOperator(infix[i]))
				{
					tmp += infix[i];
					i++;
				}
				double num=atof(tmp.c_str());
				news += num;
			}
			
		}
		return news;
	}

	double Calculator()
	{
		Stack<char> cons;
		string tmp;
		Input(postfix);
		for (int i = 0; i < infix.size(); i++)
		{
			if (!IsOperator(infix[i]) && infix[i] != ')' && infix[i] != '(')
			while (infix[i]!='.')
				{
					tmp += postfix[i];
					i++;
				}
				cons.Push(atof(tmp.c_str()));
			
			if (IsOperator(infix[i]))
			{
				double b = cons.Pop();
				double c = cons.Pop();
				double res = count(b, c, infix[i]);
				cons.Push(res);
			}
		}
		return cons.Pop();
	}

	bool Good_symb(string s) //проверка на недопустимые символы

	{
		for (int i = 0; i < s.size(); i++)
		{
			if ((int(s[i]) >= 65 && int(s[i]) <= 90) || (int(s[i]) >= 97 && int(s[i]) <= 122) || (isdigit(s[i])!=0) || (s[i] == ')') || (s[i] == '(') || IsOperator(s[i]) || (s[i] == '.'))
				return true;
			else return false;
		}
	}


	bool Brackets()//проверка на расстановку скобок
	{
		int left = 0, right = 0;
		for (int i = 0; i < infix.size(); i++)
		{
			if (infix[i] == '(')
				left++;
			else if (infix[i] == ')')
				right++;
			if (right > left)
				throw "error in brackets";
		}
		if (left == right)
			return true;
		else return false;
	}


	bool Term()//проверка на колличество операндов и операций
	{
		int operands = 0, operations = 0;
		for (int i = 0; i < infix.size(); i++)
		{
			if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/')
				operations++;
			else if (!IsOperator(infix[i]))
			{
				while (infix[i] != '+' && infix[i] != '-'  && infix[i] != '*'  && infix[i] != '/')
				{
					i++;
					if (i == infix.size())
						break;
				}
				i--;
				operands++;
			}
		}
		if (operands == operations + 1)
			return true;
		else return false;
	}
};
#endif _ARITHMETIC_H_ 