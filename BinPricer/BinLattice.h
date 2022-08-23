
#ifndef BINLATTICE_H_INCLUDED
#define BINLATTICE_H_INCLUDED


#include "Option.h"
#include <math.h>
#include <vector>
using namespace std;


enum Type {Euro,Digi};
template <class T>
class BinLattice
{
private:
	double m_r; //interest rate
	double m_sigma; //volatility
	double m_K; //strike price
	double m_T; //maturity
	double m_S; //underlying price
	double m_q; //yield
	// b=r-q
	Opt m_option;
	int m_n;
	vector < vector <T> > m_Lattice;
	Type m_type;

public:
	//BinLattice();
	BinLattice(double r, double sigma, double K, double U, double S, double q, Opt option,int n, Type type);
	void SetN();
	long combi(int long n, int long k);
	void SetNode(int n, int i, double val);
	double CalNode(int n, int i);
	double payoff(double price, Type type);
	double GetNode(int n, int i);
	void Display();
};



// ccp
template <class T>
BinLattice<T>::BinLattice(double r, double sigma, double K, double U, double S, double q, Opt option, int n, Type type)
{
	this->m_r = r;
	this->m_K = K;
	this->m_sigma = sigma;
	this->m_T = U;
	this->m_S = S;
	this->m_q = q;
	this->m_option = option;
	this->m_n = n;
	this->m_type = type;
}

template <class T>
void BinLattice<T>::SetN()
{
	for (int i = 0; i <= m_n; i++)
	{
		m_Lattice.push_back(vector<double>(i + 1));
	}
}

template <class T>
double BinLattice<T>::payoff(double price, Type type) // on veut afficher pour t=0
{
	double rlt = 0;
	if (type == Euro)
	{
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

	//elsehas no member named 'pop_back'

	{
		if (m_option == put)
		{
			rlt = (m_K - price > 0) ? 1 : 0;

		}
		else // cas d'un call
		{
			rlt = (price - m_K > 0) ? 1 : 0;
		}
		return rlt;
	}
}

template <class T>
double BinLattice<T>::CalNode(int n, int i)
// n indique la colonne, i la ligne (ie) i est la ième valeur de la colonne n
{
	double rlt = 0;
	double price = 0;
	double pay = 0;
	long int combin = 0;

	double delta = m_T / m_n;
	double u = exp(m_sigma * sqrt(delta));
	double d = 1 / u;
	double p = (exp((m_r - m_q) * delta) - d) / (u - d);

	for (int k = 0; k <= m_n - n; k++)
	{
		// knowing that S(n,i) = m_S*d^i*u^(n-i) and d=1/u
		//then S(n,i) = m_S*u^(n - 2*i)
		//then S(m_n,k+i) = m_S^(m_n - 2*(k+i))
		price = m_S * pow(u, m_n - 2 * (k + i));
		pay = payoff(price, m_type);
		combin = combi(m_n - n, k);
		rlt = rlt + combin * pow(1 - p, k) * pow(p, m_n - n - k) * pay;
	}
	// 1/(1+R)^N ~ exp(-R*delta*N) = exp(-R*T)
	// 1/(1+R)^(N-n) ~ exp(-R*delta*(N-n))
	rlt = rlt * exp(-m_r * delta * (m_n-n));
	m_Lattice[n][i] = rlt;
	return rlt;
}

template <class T>
long BinLattice<T>::combi(int long n, int long k)
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

template <class T>
void BinLattice<T>::SetNode(int n, int i, double val)
{
	m_Lattice[n][i] = val;
}

template <class T>
double BinLattice<T>::GetNode(int n, int i)
{
	//SetNode(n, i);
	double rlt = m_Lattice[n][i];
	return rlt;
}

template <class T>
void BinLattice<T>::Display()
{
	// on choisit d'affecter 4 unités pour un nombre
	// il y a m_n + 1 nombres sur la dernière colonne
	string esp = "    ";
	for (int i = 1; i <= m_n; i++)
		esp += "    ";

	string nbre = "";
	//bool slah = true;
	//true = "/____" (suivi de 4 unités vides) et false = "\__" (suivi de 2 unités vide)
	int ligne = 0; // paire on affiche les prix, impairs on affiche les "/" "\"
	int index = 0; // permet de lire la index-ième colonne de Lattice
	while (index <= m_n)
	{
		if (ligne % 2 == 0) //on affiche les prix
		{
			cout << esp;
			for (int k = 0; k < m_Lattice[index].size(); k++)
			{
				//nbre = to_string(m_Lattice[index][k]); --> on l'utilise que si le vector m_Lattice est tout remplie
				nbre = to_string(CalNode(index, k));
				for (int l = 0; l < 4; l++) // afficher les 4 premiers caractères du price
					cout << nbre[l];
				cout << "    "; // séparation entre les prices
			}
			cout << endl; // ligne suivante
			esp.pop_back(); // on enmève un espace pour ajouter / sur la ligne suivante
			index += 1; // pour pouvoir aller à la colonne suivante
			ligne += 1; // on va à la ligne suivante
		}
		else
		{
			cout << esp;
			for (int p = 0; p < sizeof(m_Lattice[index - 1]); p++) // on fait autant de fois que le nbre de prices qu'on a affiché juste avant
			{
				cout << "/    \\  ";
			}
			cout << endl;
			ligne += 1;
			esp.pop_back();
			esp.pop_back();
			esp.pop_back();
		}
	}
}


#endif // BINLATTICE_H_INCLUDED


