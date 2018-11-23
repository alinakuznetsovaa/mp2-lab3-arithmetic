// объявление функций и классов для вычисления арифметических выражений
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
		int j = 0;
		
		for (int i = 0; i <infix.size(); i++)
		{
			if (!IsOperator(infix[i]) && infix[i] != '(' && infix[i] != ')')
			{
				if (infix[i] != ' ')
				{
					int j = i;
					while (!IsOperator(infix[j]) && j != infix.size() && infix[j] != ')' && infix[j] != ' ')
					{
						postfix += infix[j];
						j++;
					}
					i = j - 1;
					postfix += ','; //разделяю элементы запятыми
				}
			}

			else
				if (infix[i] == '-')
				{
					if (i == 0)
						postfix += infix[0];
					else
						if (postfix[postfix.size() - 1] == '-')
							postfix.erase(postfix.size() - 1);
						else
							goto metka;
				}
				else
					metka:if (opers.IsEmpty() || opers.CheckTopEl() == '(')
					{
						if (infix[i] == ')')
							opers.Pop();
						else
							opers.Push(infix[i]);
					}
					else
						if (Priority(infix[i], opers.CheckTopEl()) == 1)
							opers.Push(infix[i]);
					else
						if (Priority(infix[i], opers.CheckTopEl()) <= 0)
						{
							while ((!opers.IsEmpty()) && (opers.CheckTopEl() != '(' || Priority(opers.CheckTopEl(), infix[i]) != -1))
							{
								postfix += opers.Pop();
								postfix += ',';
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
									{
										postfix += opers.Pop();
										postfix += ',';
									}
									opers.Pop();
								}
		}
		while (!opers.IsEmpty())
		{
			postfix += opers.Pop();
			postfix += ',';
		}
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
			res = a / b;
		}

		return res;
	}


	double Calculator()
	{
		double res;
		Stack<double> nums(postfix.size());
		vector<string> letts;
		vector<double> values;

		for (int i = 0; i < postfix.size(); i++)
		{
			if ((int(postfix[i]) >= 65 && int(postfix[i]) <= 90) || ((int(postfix[i]) >= 97 && int(postfix[i]) <= 122)))
			{
				string lett;
				lett += postfix[i];
				int temp = 0;
				i++;
				while (postfix[i] != ',')
				{
					lett += postfix[i];
					i++;
				}
				for (int i = 0; i < letts.size(); i++)
				{
					if (letts[i] == lett)
						temp++;
				}
				if (temp == 0)
					letts.push_back(lett);
				
			}
		}

		for (int i = 0; i < letts.size(); i++)
		{
			int tmp;
			cout << "Input value of variable: " << letts[i] << ':';
			cin >> tmp;
			values.push_back(tmp);
		}


		for (int i = 0; i < postfix.size(); i++)
		{
			if (!IsOperator(postfix[i]))
			{
				if ((int(postfix[i]) >= 65 && int(postfix[i]) <= 90) || ((int(postfix[i]) >= 97 && int(postfix[i]) <= 122)))
				{
					string lett;
					lett += postfix[i];
					i++;
					while (postfix[i] != ',')
					{
						lett += postfix[i];
						i++;
					}
					for (int i = 0; i < letts.size(); i++)
					{
						if (letts[i] == lett)                      
							nums.Push(values[i]);
					}
					
				}
				else
				{
					string tmp;
					tmp += postfix[i];
					i++;
					while (postfix[i] != ',')
					{
						tmp += postfix[i];
						i++;
					}
					nums.Push(atof(tmp.c_str())); // atof из string в double
				}
			}
			else
			{
				if (postfix[i] == '-')
				{
					if (postfix[i + 1] == ',')
					{
						nums.Push(count(nums.Pop(), nums.Pop(), postfix[i]));
						i++;
					}
					else

					if (isdigit(postfix[i+1]))
					{
						i++;
						string tmp;
						tmp += postfix[i];
						i++;
						while (postfix[i] != ',')
						{
							tmp += postfix[i];
							i++;
						}
						nums.Push(-(atof(tmp.c_str())));
					}
					else
						if ((int(postfix[i + 1]) >= 65 && int(postfix[i + 1]) <= 90) || ((int(postfix[i + 1]) >= 97 && int(postfix[i + 1]) <= 122)))
						{
							i++;
							string lett;
							lett += postfix[i];
							i++;
							while (postfix[i] != ',')
							{
								lett += postfix[i];
								i++;
							}
							for (int i = 0; i < letts.size(); i++)
							{
								if (letts[i] == lett)
									nums.Push(-(values[i]));
							}
						}
				}
				else
					{
						nums.Push(count(nums.Pop(), nums.Pop(), postfix[i]));
						i++;
					}
						
				}
			}
		
		return nums.CheckTopEl();
	}

	bool Error(){
		bool res = true;
		int l = 0;
		Stack<char> x(infix.size());
		int t = 0;
		char brasc;
		if (infix.empty())
		{
			cout << " string is empty" << endl;
			return false;
		}
		else
		{
			if ((infix[0] == '+') || (infix[0] == '*') || (infix[0] == '/') ||  (infix[0] == ')') || (infix[0] == '.'))
			{
				res = false;
				cout << "wrong begin of expression" << endl;
			}
			if (IsOperator(infix[infix.size() - 1]) || (infix[infix.size() - 1] == '(') || (infix[infix.size() - 1] == '.'))
			{
				res = false;
				cout << "wrong end of expression" << endl;
			}
		}

		for (int i = 0; i < infix.size() - 2; i++)
		{

			if (infix[i] == '.')
			{
				if (isdigit(infix[i + 1]) == 0)
				{
					cout << "spelling error" << endl;
					res = false;
				}
			}
		}
		for (int i = 0; i < infix.size() - 2; i++)
			{

				if (infix[i] == ')')
				{
					if ((isdigit(infix[i + 1]) != 0) || (int(infix[i + 1]) >= 65 && int(infix[i + 1]) <= 90) || ((int(infix[i + 1]) >= 97 && int(infix[i + 1]) <= 122)) || (infix[i + 1] == '.'))
					{
						cout << "spelling error" << endl;
						res = false;
					}
				}
		}
		for (int i = 0; i < infix.size() - 2; i++)
			{

				if (infix[i] == '+' || infix[i] == '*' || infix[i] == '/')
				{
					if (infix[i + 1] == '+' || infix[i + 1] == '*' || infix[i + 1] == '/')
					{
						cout << "several operations in a row" << endl;
						res = false;
					}
				}
		}
		for (int i = 0; i < infix.size() - 2; i++)
		{

			if (infix[i] == '(')
			{
				if ((infix[i + 1] == ')') || (infix[i + 1] == '.'))
				{
					cout << "spelling error" << endl;
					res = false;
				}
			}
		}
		
		for (int i = 0; i < infix.size(); i++)
		{
			if (!((int(infix[i]) >= 65 && int(infix[i]) <= 90) || (int(infix[i]) >= 97 && int(infix[i]) <= 122) || (isdigit(infix[i]) != 0) || (infix[i] == ')') || (infix[i] == '(') || IsOperator(infix[i]) || (infix[i] == '.') || (infix[i] == ' ')))
			{
				cout << "invalid symbol on " << i+1 << " position" << endl;
				res = false;
			}
			
			if (infix[i] == '(')
				x.Push('(');
			else
				if (infix[i] == ')')
				{
					if (!(x.IsEmpty()))
					{
						brasc= x.Pop();
					}
					else
					{
						t++;
					}
				}
		}	
		if (t != 0) {
			res = false;
			cout << "error in brackets" << endl;
		}
		return res;
	}
};
#endif _ARITHMETIC_H_ 