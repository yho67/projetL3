#include "Table.h"

#include <iostream>
#include <vector>

#include "Joueur.h"


using namespace std;

Table::Table()
{
  //constructeur par défaut 
	m_nbre_max_joueur = 1;
	Joueur player_default;
	m_tabjoueur.push_back(player_default); //si aucun paramètre, un seul joueur au maximum
  	m_tabmise.push_back(0) ; //pas de mise au départ
}

Table::Table(int const nbre_max_joueur)
{
  //constructeur
	m_nbre_max_joueur = nbre_max_joueur;
	Joueur player_default;
	for(int i=0; i<nbre_max_joueur;i++)
	{
		m_tabjoueur.push_back(player_default); // on a un tableau de siège vide
	} 
  	for(int i=0; i<nbre_max_joueur;i++)
	{
		m_tabmise.push_back(0); // on initialise toutes les mises à 0
	}
}

Table::~Table()
{
  //destructeur
}

void Table::Paye(int numero_joueur, int multiplicateur)
{
	// on connait le numéro du joueur qui est dans sa classe, ce qui donne son indice dans la table de mise également. Donc on peut modifier l'argent du joueur et la table de mise.
	int money = m_tabjoueur[numero_joueur].GetArgent();
	money += m_tabmise[numero_joueur]*multiplicateur;
	m_tabjoueur[numero_joueur].SetArgent(money);
	//et on remet sa mise à 0
	m_tabmise[numero_joueur] = 0;
}

void Table::ModifMiseJoueur(int numero_joueur, int mise)
{
	// si on passe -1 en argument de mise, ça veut dire de remettre à 0. Sinon on additione la mise déjà présente avec la nouvelle.
	if(mise==-1)
	{
		m_tabmise[numero_joueur] =0;
	}
	else
	{
		m_tabmise[numero_joueur] += mise;
	}
}


Joueur* Table::AjouterJoueur()
{
	// on vérifie qu'il y a encore des sièges vides, si oui, on le remplace par le joueur, on modifie le numéro du joueur pour qu'il corresponde à son indice dans le tableau
	for(int i=0;i<m_nbre_max_joueur;i++)
	{
		if(m_tabjoueur[i].GetNumero()==-1)//si c'est un siège vide
		{
			m_tabjoueur[i].SetNumero(i); // on désigne le numéro du joueur ...
			m_tabjoueur[i].SetTable(this); // .. et on lui dit qu'il joue a cette table
			return &m_tabjoueur[i];
		}
	}
	//si on est ressorti de la boucle, c'est qu'il n'y avait plus de place
	return 0;
}

void Table::EnleverJoueur(int numero_joueur)
{
	Joueur player_default;
	m_tabjoueur[numero_joueur] = player_default;
}

