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
	virtual double MCPricer(double S, double T, int n_sample, int sample_size) const= 0;
	double BoxMuller(double mean, double var) const;
	virtual double payoff(double price) const= 0;
	double GetS();
	double GetT();
	double N(double x);
	double BSPricer() ;
	~Option();
};




#endif // OPTION_H_INCLUDED
