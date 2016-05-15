#include "Carte.h"
#include <iostream>
#include <string>

using namespace std;

Carte::Carte()
{
//constructeur par défaut
	m_numero = 0;
	m_valeur = 0;
	m_symbol = "nul";
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
	//passons au symbol
	if(numero<=10 && numero >=2)
	{
		m_symbol = to_string(numero);
	}
	else if(numero == 1)
	{
		m_symbol = "As"; //l'as
	}
	else if(numero == 11)
	{
		m_symbol = "J";//valet
	}
	else if(numero == 12)
	{
		m_symbol = "Q";//dame
	}
	else if(numero == 13)
	{
		m_symbol = "K";//roi
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
	m_couleur = A.GetCouleur();
	m_symbol = A.GetSymbol();
}

void Carte::ChangeValeurAs(int valeur)
{
	//on vérifie bien que c'est un as sur lequel on a appelé la méthode
	if(m_numero == 1)
	{
		m_valeur = valeur;
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
	//passons au symbol
	if(numero<=10 && numero >=2)
	{
		m_symbol = to_string(numero);
	}
	else if(numero == 1)
	{
		m_symbol = "As"; //l'as
	}
	else if(numero == 11)
	{
		m_symbol = "J";//valet
	}
	else if(numero == 12)
	{
		m_symbol = "Q";//dame
	}
	else if(numero == 13)
	{
		m_symbol = "K";//roi
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
	return;
}



