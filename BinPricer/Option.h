#ifndef OPTION_H_INCLUDED
#define OPTION_H_INCLUDED

#pragma once

#include <string>
#include <iostream> /*cout, endl*/
#include <stdlib.h> /*srand(), rand()*/
#include <time.h> /*time()*/
#include <math.h> /*sqrt*/
#include <vector>

enum Opt { call, put };

class Option
{
protected:
	double m_r; //interest rate
	double m_sigma; //volatility
	double m_K; //strike price
	double m_T; //maturity
	double m_S; //underlying price
	double m_q; //yield
	// b=r-q
	Opt m_option;

public:
	Option();
	double N(double x);
	double BSPricer();
	long combi(int long n, int long k);
	virtual double BinPricer(int n) = 0;
	virtual double BinPricer2(int n) = 0;
	virtual double payoff(double price) = 0;
};



#endif // OPTION_H_INCLUDED

