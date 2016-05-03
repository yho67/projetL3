#include "Carte.h"
#include <iostream>
#include <string>

using namespace std;

Carte::Carte()
{
//constructeur par défaut
	m_numero = 0;
	m_valeur = 0;
	m_couleur = "nul";
}

Carte::Carte(int numero, string couleur)
{
//constructeur 
	// on vérifie que le numéro est entre 1 et 13 (11 = valet, 12 = dame, 13 = roi)
	if(numero<= 13 && numero>=1)
	{
		m_numero = numero;
	}
	else
	{
		cout<<" mauvais numero"<<endl;
	}	
	//on vérifie que la couleur est une des 4
	if(couleur == "coeur" || couleur == "carreau" || couleur == "pique" || couleur == "trefle")
	{
		m_couleur = couleur;
	}
	else
	{
		cout<< "mauvaise couleur"<<endl;
		m_couleur = "nul";
	}
	//enfin on s'occupe de la valeur (10 pour les tetes, numero=valeur pour le reste, as = 11 de base)
	if(numero<=10 && numero >=2)
	{
		m_valeur = numero;
	}
	else if(numero == 1)
	{
		m_valeur = 11; //l'as
	}
	else
	{
		m_valeur = 10;//les tetes
	}
}

Carte::~Carte()
{
//destructeur
}

Carte::Carte(Carte & A)
{
 //constructeur de recopie
	m_numero = A.GetNumero();
	m_valeur = A.GetValeur();
	string a = A.GetCouleur();
	m_couleur = a;
}

void Carte::ChangeValeurAs()
{
	//on vérifie bien que c'est un as sur lequel on a appelé la méthode
	if(m_numero == 1)
	{
		m_valeur = 1;
	}
	else
	{	
		cout<<" ce n'est pas un as"<<endl;
		return;
	}
}

void Carte::Initialise(int numero, string couleur)
{
	// on vérifie que le numéro est entre 1 et 13 (11 = valet, 12 = dame, 13 = roi)
	if(numero<= 13 && numero>=1)
	{
		m_numero = numero;
	}
	else
	{
		cout<<" mauvais numero"<<endl;
		m_numero =0;
	}	
	//on vérifie que la couleur est une des 4
	if(couleur == "coeur" || couleur == "carreau" || couleur == "pique" || couleur == "trefle")
	{
		m_couleur = couleur;
	}
	else
	{
		cout<< "mauvaise couleur"<<endl;
		m_couleur = "nul";
	}
	if(numero<=10 && numero >=2)
	{
		m_valeur = numero;
	}
	else
	{
		m_valeur = 10;
	}
	return;
}



