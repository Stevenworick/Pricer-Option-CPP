#include "AsianOpt.h"


AsianOpt :: AsianOpt(double r, double sigma, double K, double T, double S, double q, Opt option)
{
	this->m_r = r;
	this->m_K = K;
	this->m_sigma = sigma;
	this->m_T = T;
	this->m_S = S;
	this->m_q = q;

	this->m_option = option;
}

/*
double AsianOpt::GetS()
{
	return m_S;
}

double AsianOpt::GetT()
{
	return m_T;
}
*/

double AsianOpt :: MCPricer(double S, double T, int n_sample, int sample_size) const
{
	double rlt = 0;
	double delta = T / sample_size;
	double prix;
	double Z;
	double pay;


	for (int j = 1; j <= n_sample; j++)
	{
		prix = 0;
		Z = 0;
		for (int i = 1; i <= sample_size; i++)
		{
			Z += BoxMuller(0.0, 1.0);
			prix += S * exp(i * (m_r - pow(m_sigma, 2) / 2) * delta + m_sigma * sqrt(delta) * Z);
		}

		pay = payoff(prix/sample_size);
		rlt += pay;
	}

	return exp(-m_r * m_T) * rlt / n_sample;
}

double AsianOpt ::payoff(double price) const
{
	double rlt = 0;
	if (m_option == put)
	{
		rlt = (m_K - price > 0) ? (m_K - price) : 0;

	}
	else // cas d'un call
	{
		rlt = (price - m_K > 0) ? (price - m_K) : 0;
	}
	return rlt;
}

AsianOpt::~AsianOpt()
{
}
