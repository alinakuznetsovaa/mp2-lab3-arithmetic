// реализация пользовательского приложения
#include <iostream>
#include "arithmetic.h"
#include <string>

using namespace std;

int main()

{
	bool res = true;
	int k;
	cout << "Menu:" << endl;
	cout << "1.Enter expression " << endl;
	cout << "2.Exit" << endl;

	while (res)

	{
		cout << "Input a menu number:" << endl;
		cin >> k;
		switch (k) {
		case 1:
		{
			string tmp;
			cout << "Enter expression:";
			cin.ignore();
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
			res = false;
			break;
		}
		default:
		{
			cout << "wrong menu number" << endl;
			cout << "try again" << endl;
		}
		}
	}
	return 0;
}