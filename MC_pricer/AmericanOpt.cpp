#include "AmericanOpt.h"
#include <math.h>
#include "Option.h"

using namespace std;

AmericanOpt::AmericanOpt(double r, double sigma, double K, double T, double S, double q, Opt option)
{
	this->m_r = r;
	this->m_K = K;
	this->m_sigma = sigma;
	this->m_T = T;
	this->m_S = S;
	this->m_q = q;

	this->m_option = option;
}

double AmericanOpt::payoff(double price) const // on veut afficher pour t=0
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

AmericanOpt::~AmericanOpt()
{
}

double AmericanOpt::MCPricer(double S, double T, int n_sample, int sample_size) const
{
	vector <double> tab (sample_size,0);

	double rlt = 0;
	double delta = T / sample_size;
	double prix;
	double Z;
	double pay;
	int indice_max = 0;


	for (int j = 1; j <= n_sample; j++)
	{
		//somme = 0;
		Z = 0;
		for (int i = 1; i <= sample_size; i++)
		{
			Z += BoxMuller(0.0, 1.0);
			prix = S * exp(i * (m_r - pow(m_sigma, 2) / 2) * delta + m_sigma * sqrt(delta) * Z);
			pay = payoff(prix);
			tab[i - 1] += pay; // on fait la somme de tous les payoffs à la date ti sans faire la moyenne
		}
	}

	for (int k = 0; k < sample_size; k++)
	{
		if (tab[k] > rlt)
		{
			rlt = tab[k];
			indice_max = k + 1;
		}

	}

	//moyenne de rlt
	rlt = rlt / n_sample;

	return exp(-m_r * delta * indice_max) * rlt;
}
