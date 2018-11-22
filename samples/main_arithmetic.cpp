// реализация пользовательского приложения
#include <iostream>
#include "arithmetic.h"
#include <string>
using namespace std;
int main()
{
	//Arithmetic x("())(");
	//if (x.Error()) {
	//	cout << x.ToPostfix() << endl;
	//	cout << x.Calculator() << endl;
	//}
	
	bool res;
	int k;
	cout << "Menu:" << endl;
	cout << "1.Enter expression " << endl;
	cout << "2.Exit" << endl;
	while (true) 
	{
		
		cout << "Input a menu number:" << endl;
		cin >> k;
		switch (k) {
		case 1:
		{
			string tmp;
			cout << "Enter expression without spaces:";
			getline(cin, tmp);
			cout << tmp << endl;
			Arithmetic x(tmp);
			cout << endl;
			if (x.Error())
			{
				cout << x.ToPostfix() << endl;
				cout << x.Calculator() << endl;
			}
			else
			{
				cout << "try again" << endl;
			}
			break;
		}
		case 2:
		{
			break;
		}
		}
	}

	return 0;
}