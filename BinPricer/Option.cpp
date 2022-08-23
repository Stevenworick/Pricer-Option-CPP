#include "Option.h"


Option::Option() : m_r(0), m_sigma(0), m_K(0), m_T(0), m_S(0), m_q(0), m_option(call)
{
using namespace std;
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

long Option::combi(int long n, int long k)
{

	int long i;
	int long b;
	if (0 == k || n == k) {
		return 1;
	}
	if (k > n) {
		return 0;
	}
	if (k > (n - k)) {
		k = n - k;
	}
	if (1 == k) {
		return n;
	}
	b = 1;
	for (i = 1; i <= k; ++i) {
		b *= (n - (k - i));
		if (b < 0) return -1;
		b /= i;
	}
	return b;
}
