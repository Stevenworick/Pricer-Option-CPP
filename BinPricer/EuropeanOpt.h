#ifndef EUROPEANOPT_H_INCLUDED
#define EUROPEANOPT_H_INCLUDED

#pragma once

#include "Option.h"

class EuropeanOpt : public Option
{
public:
	//EuropeanOpt();
	EuropeanOpt(double r, double sigma, double K, double T, double S, double q, Opt option);
	double BinPricer(int n);
	double payoff(double price);
	double BinPricer2(int n);
};



#endif // EUROPEANOPT_H_INCLUDED


