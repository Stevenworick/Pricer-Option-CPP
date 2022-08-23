#include <iostream>
#include "European.h"
#include "AsianOpt.h"
#include "AmericanOpt.h"
#include<stdlib.h>
using namespace std;

int main()
{
    AsianOpt t1(0.05, 0.25, 60.0, 2, 62.0, 0.0, call);
	AsianOpt t2(0.05, 0.25, 80.0, 2, 82.0, 0.0, call);
	AsianOpt t3(0.05, 0.25, 100.0, 2, 102.0, 0.0, call);
	AsianOpt p1(0.05, 0.25, 60.0, 2, 62.0, 0.0, put);
	AsianOpt p2(0.05, 0.25, 80.0, 2, 82.0, 0.0, put);
	AsianOpt p3(0.05, 0.25, 100.0, 2, 102.0, 0.0, put);

	double r1 = t1.MCPricer(t1.GetS(), t1.GetT(), 5000,300);
	double r2 = t2.MCPricer(t2.GetS(), t2.GetT(), 5000,300);
	double r3 = t3.MCPricer(t3.GetS(), t3.GetT(), 5000,300);
	double o1 = p1.MCPricer(p1.GetS(), p1.GetT(), 5000, 300);
	double o2 = p2.MCPricer(p2.GetS(), p2.GetT(), 5000, 300);
	double o3 = p3.MCPricer(p3.GetS(), p3.GetT(), 5000, 300);

	cout << "Asian Option" << endl;
	cout << "price MC call 1 : " << r1 << endl;
	cout << "price MC call 2 : " << r2 << endl;
	cout << "price MC call 3 : " << r3 << endl;
	cout << "price MC put 1 : " << o1 << endl;
	cout << "price MC put 2 : " << o2 << endl;
	cout << "price MC put 3 : " << o3 << endl;

	AmericanOpt a1(0.05, 0.25, 60.0, 2, 62.0, 0.0, call);
	AmericanOpt a2(0.05, 0.25, 80.0, 2, 82.0, 0.0, call);
	AmericanOpt a3(0.05, 0.25, 100.0, 2, 102.0, 0.0, call);
	AmericanOpt b1(0.05, 0.25, 60.0, 2, 62.0, 0.0, put);
	AmericanOpt b2(0.05, 0.25, 80.0, 2, 82.0, 0.0, put);
	AmericanOpt b3(0.05, 0.25, 100.0, 2, 102.0, 0.0, put);

	double c1 = a1.MCPricer(t1.GetS(), t1.GetT(), 5000, 300);
	double c2 = a2.MCPricer(t2.GetS(), t2.GetT(), 5000, 300);
	double c3 = a3.MCPricer(t3.GetS(), t3.GetT(), 5000, 300);
	double d1 = b1.MCPricer(p1.GetS(), p1.GetT(), 5000, 300);
	double d2 = b2.MCPricer(p2.GetS(), p2.GetT(), 5000, 300);
	double d3 = b3.MCPricer(p3.GetS(), p3.GetT(), 5000, 300);

	cout << endl << "American Option" << endl;
	cout << "price MC call 1 : " << c1 << endl;
	cout << "price MC call 2 : " << c2 << endl;
	cout << "price MC call 3 : " << c3 << endl;
	cout << "price MC put 1 : " << d1 << endl;
	cout << "price MC put 2 : " << d2 << endl;
	cout << "price MC put 3 : " << d3 << endl;

    European l1(0.05, 0.25, 60.0, 2, 62.0, 0.0, call);
    European l2(0.05, 0.25, 80.0, 2, 82.0, 0.0, call);
	European l3(0.05, 0.25, 100.0, 2, 102.0, 0.0, call);
    European w1(0.05, 0.25, 60.0, 2, 62.0, 0.0, put);
    European w2(0.05, 0.25, 80.0, 2, 82.0, 0.0, put);
	European w3(0.05, 0.25, 100.0, 2, 102.0, 0.0, put);

	double E1 = l1.MCPricer(l1.GetS(), l1.GetT(), 5000, 300);
	double E2 = l2.MCPricer(l2.GetS(), l2.GetT(), 5000, 300);
	double E3 = l3.MCPricer(l3.GetS(), l3.GetT(), 5000, 300);
	double F1 = w1.MCPricer(w1.GetS(), w1.GetT(), 5000, 300);
	double F2 = w2.MCPricer(w2.GetS(), w2.GetT(), 5000, 300);
	double F3 = w3.MCPricer(w3.GetS(), w3.GetT(), 5000, 300);

	cout << endl << "European Option" << endl;
	cout << "price MC call 1 : " << E1 << endl;
	cout << "price MC call 2 : " << E2 << endl;
	cout << "price MC call 3 : " << E3 << endl;
	cout << "price MC put 1 : " << F1 << endl;
	cout << "price MC put 2 : " << F2 << endl;
	cout << "price MC put 3 : " << F3 << endl;


	double G1 = l1.BSPricer();
	double G2 = l2.BSPricer();
	double G3 = l3.BSPricer();
	double H1 = w1.BSPricer();
	double H2 = w2.BSPricer();
	double H3 = w3.BSPricer();

	cout << endl << "European Option" << endl;
	cout << "price BS call 1 : " << G1 << endl;
	cout << "price BS call 2 : " << G2 << endl;
	cout << "price BS call 3 : " << G3 << endl;
	cout << "price BS put 1 : " << H1 << endl;
	cout << "price BS put 2 : " << H2 << endl;
	cout << "price BS put 3 : " << H3 << endl;

	return 0;
}
