
#ifndef DIGITALOPT_H_INCLUDED
#define DIGITALOPT_H_INCLUDED

#pragma once

#include "Option.h"

class DigitalOpt : public Option
{
public:
	//DigitalOpt();
	DigitalOpt(double r, double sigma, double K, double T, double S, double q, Opt option);
	double BinPricer(int n);
	double payoff(double price);
	double BinPricer2(int n);
};



#endif // DIGITALOPT_H_INCLUDED

