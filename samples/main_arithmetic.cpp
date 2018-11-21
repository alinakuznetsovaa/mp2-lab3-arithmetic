// реализация пользовательского приложения
#include <iostream>
#include "arithmetic.h"
#include <string>
using namespace std;
int main()
{
	Arithmetic x("12.5+(4*7)");
	/*cout << x.NewInfix();*/
	cout << x.ToPostfix() << endl;
	//cout << x.Calculator() << endl;
	system("pause");
  return 0;
}
