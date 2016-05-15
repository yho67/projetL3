#include "Joueur.h"

#include <iostream>
#include <vector>


#include "Table.h"

using namespace std;

Joueur::Joueur()
{
  //constructeur par défaut 
	m_numero = -1; // on l'initialise comme un siège vide si rien de précisé.
  	m_argent = 0;
  	m_pseudo = ""; //les cartes que le joueur a sur la table
}

Joueur::Joueur(int numero, int argent, std::string pseudo, std::vector<Carte*> main, Table* ptable) : Participant(main, ptable), m_numero(numero), m_argent(argent), m_pseudo(pseudo)
{
  //constructeur
}

Joueur::Joueur(Joueur const& joueur)
{
  //constructeur de recopie
	m_numero = joueur.m_numero;
	m_argent = joueur.m_argent;
	m_pseudo = joueur.m_pseudo;
	m_main = joueur.m_main; //les vecteurs ont un système de copie efficace
	m_ptable = joueur.m_ptable;
}

void Joueur::Initialise(int numero, int argent, std::string pseudo, std::vector<Carte*> main, Table* ptable)
{
	m_numero = numero;
	m_argent = argent;
	m_pseudo = pseudo;
	m_main = main;
	m_ptable = ptable;
}

void Joueur::Miser(int mise, Table* table)
{
	// on vérifie d'abord qu'on ne mise pas plus que l'argent que l'on a ou une somme négative
	if(mise>m_argent)
	{
		cout<<"Pas assez d'argent pour miser cette somme"<<endl;
	}
	else if(mise<0) 
	{
		cout<<"On ne peut pas miser une somme negative"<<endl;
	}
	else
	{
		//si tout est bon, on baisse l'argent du joueur et on enregistre sa mise;
		m_argent -= mise;
		table->ModifMiseJoueur(m_numero, mise); //on enregistre sa mise supplémentaire dans la table des mises
	}
}

bool Joueur::Perdu()
{
	bool perdu = Participant::Perdu(); // on veut rajouter le changement des mises à la méthode porté définie dans Personnage
	if(perdu)
	{
		m_ptable->ModifMiseJoueur(m_numero, -1); // on remet la mise du joueur a 0;
	}
	return perdu;	
}



