#ifndef EUROPEAN_H_INCLUDED
#define EUROPEAN_H_INCLUDED


#pragma once

#include "Option.h"

class European : public Option
{
public:
	//EuropeanOpt();
	European(double r, double sigma, double K, double T, double S, double q, Opt option);
	double MCPricer(double S, double T, int n_sample, int sample_size) const;
	double payoff(double price) const;
	~European();
};


#endif // EUROPEAN_H_INCLUDED
