#include "European.h"
#include <math.h>
#include "Option.h"

using namespace std;

/*
EuropeanOpt::EuropeanOpt()
{

}
*/

European::European(double r, double sigma, double K, double T, double S, double q, Opt option)
{
	this->m_r = r;
	this->m_K = K;
	this->m_sigma = sigma;
	this->m_T = T;
	this->m_S = S;
	this->m_q = q;

	this->m_option = option;
}

double European::payoff(double price) const // on veut afficher pour t=0
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

European::~European()
{
}

/*
double European::GetS()
{
	return m_S;
}

double European::GetT()
{
	return m_T;
}
*/

double European ::MCPricer(double S, double T, int n_sample, int sample_size) const
{
	double rlt = 0;
	double delta = T / sample_size;
	double prix;
	double Z;
	double pay;


	for (int j = 1; j <= n_sample; j++)
	{
		//somme = 0;
		Z = 0;
		for (int i = 0; i <= sample_size - 1; i++)
		{
			Z += BoxMuller(0.0, 1.0);
		}
		prix = S * exp(sample_size * (m_r - pow(m_sigma, 2) / 2) * delta + m_sigma * sqrt(delta) * Z);
		pay = payoff(prix);
		rlt += pay;
	}

	return exp(-m_r*m_T)* rlt / n_sample;
}
