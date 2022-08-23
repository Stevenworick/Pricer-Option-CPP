#ifndef AMERICANOPT_H_INCLUDED
#define AMERICANOPT_H_INCLUDED

#pragma once

#include "Option.h"


class AmericanOpt : public Option
{
public:
	AmericanOpt(double r, double sigma, double K, double T, double S, double q, Opt option);
	double MCPricer(double S, double T, int n_sample, int sample_size) const;
	double payoff(double price) const;
	~AmericanOpt();
};




#endif // AMERICANOPT_H_INCLUDED
