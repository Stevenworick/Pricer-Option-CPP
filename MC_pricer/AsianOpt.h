#ifndef ASIANOPT_H_INCLUDED
#define ASIANOPT_H_INCLUDED

#pragma once

#include "Option.h"


class AsianOpt : public Option
{
public:
	AsianOpt(double r, double sigma, double K, double T, double S, double q, Opt option);
	double MCPricer(double S, double T, int n_sample, int sample_size) const;
	double payoff(double price) const;
	//double GetS();
	//double GetT();
	~AsianOpt();
};


#endif // ASIANOPT_H_INCLUDED
