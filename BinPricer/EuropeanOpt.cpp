#include "EuropeanOpt.h"
#include <math.h>
#include "Option.h"

using namespace std;

/*
EuropeanOpt::EuropeanOpt()
{

}
*/

EuropeanOpt::EuropeanOpt(double r, double sigma, double K, double T, double S, double q, Opt option)
{
	this->m_r = r;
	this->m_K = K;
	this->m_sigma = sigma;
	this->m_T = T;
	this->m_S = S;
	this->m_q = q;
	this->m_option = option;
}

double EuropeanOpt::BinPricer(int n) // on affiche C0 (ie) dernier du tableau
{
	vector <double> tab(n + 1);
	double delta = m_T / n;
	double u = exp(m_sigma * sqrt(delta));
	for (int i = 0; i < n + 1; i++)
	{
		tab[i] = payoff(m_S * pow(u, (n - i * 2)));
	}

	double d = 1 / u;
	double p = (exp((m_r - m_q) * delta) - d) / (u - d);

	for (int j = 0; j < n; j++)
	{
		for (int k = 0; k < n - j - 1; k++)
		{
			tab[k] = exp(-m_r * delta) * (p * tab[k] + (1 - p) * tab[k + 1]);
		}
	}

	return tab[0];
}

double EuropeanOpt::payoff(double price) // on veut afficher pour t=0
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

double EuropeanOpt::BinPricer2(int n)
{
	double rlt = 0;
	double price = 0;
	double pay = 0;
	long int combin = 0;

	double delta = m_T / n;
	double u = exp(m_sigma * sqrt(delta));
	double d = 1 / u;
	double p = (exp((m_r - m_q) * delta) - d) / (u - d);

	for (int i = 0; i <= n; i++)
	{
		// knowing that S(n,i) = m_S*u^i*d^(n-i) and d=1/u
		//then S(n,i) = m_S*u^(n-2*i)
		price = m_S*pow(u, n - 2 * i); // avec que des up pr i=0, on a les mêmes valeurs que le profs
		pay = payoff(price);
		combin = combi(n, i);
		rlt = rlt + combin * pow(1 - p, i) * pow(p, n - i) * pay;

	}

	//rlt = rlt / pow(1 + m_r, n);
	rlt = rlt * exp(-m_r*m_T);

	return rlt;
}
