

#include <iostream>
#include "EuropeanOpt.h"
#include "DigitalOpt.h"
#include "BinLattice.h"
using namespace std;
int main()
{
    BinLattice<double> t(0.05, 0.25, 80.0, 2.0, 82.0, 0.0, call, 11,Euro);
	EuropeanOpt t1(0.05, 0.25, 60.0, 2.0, 62.0, 0.0, call);
	EuropeanOpt t2(0.05, 0.25, 80.0, 2.0, 82.0, 0.0, call);
	EuropeanOpt t3(0.05, 0.25, 100.0, 2.0, 102.0, 0.0, call);
	double price1 = t1.BinPricer2(11);
	double price2 = t2.BinPricer2(11);
	double price3 = t3.BinPricer2(11);
	t.SetN();
	std::cout << "call 1 : " << price1 << endl;
	std::cout << "call 2 : " << price2 << endl;
	std::cout << "call 3 : " << price3 << endl;
	t.Display();
	cout << endl;
	return 0;
}
