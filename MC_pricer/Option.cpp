#include "Option.h"


Option::~Option()
{
}

Option::Option() : m_r(0), m_sigma(0), m_K(0), m_T(0), m_S(0), m_q(0), m_option(call)
{

}

double Option::GetS()
{
	return m_S;
}

double Option::GetT()
{
	return m_T;
}

double Option :: BoxMuller(double mean, double var) const
{
	double a, b, x, y, s;
	do {
		a = rand() / (double)RAND_MAX;
		b = rand() / (double)RAND_MAX;
		x = (a * 2) - 1;
		y = (b * 2) - 1;
		s = (x * x) + (y * y);
	} while (s > 1);
	return (x * sqrt(-2 * log(s) / s) * var) + mean;
}

double Option::N(double x)
{
double rlt = 0.5 + 0.5 * erf(x / sqrt(2.0));
return rlt;
}


double Option::BSPricer() // on veut afficher pour t=0
{
	double d1 = (log(m_S / m_K) + (m_r + pow(m_sigma, 2.0) * 0.5) * m_T) / (m_sigma * sqrt(m_T));
	double d2 = d1 - m_sigma * sqrt(m_T);
	double rlt;
	if (m_option == call)
	{
		rlt = m_S * N(d1) - m_K * exp(-m_r * m_T) * N(d2);
	}
	else
	{
		rlt = m_K * exp(-m_r * m_T) * N(-d2) - m_S * N(-d1);
	}
	return rlt;
}
