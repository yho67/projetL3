#include "Joueur.h"

#include <iostream>
#include <vector>

#include "Deck.h"
#include "Table.h"

using namespace std;

Joueur::Joueur()
{
  //constructeur par défaut 
	m_numero = -1; // on l'initialise comme un siège vide si rien de précisé.
  	m_argent = 0;
  	m_pseudo = ""; //les cartes que le joueur a sur la table
}

Joueur::Joueur(int numero, int argent, std::string pseudo, std::vector<Carte*> main)
{
  //constructeur
}

Joueur::~Joueur()
{
  //destructeur
}

Joueur::Joueur(Joueur &)
{
  //constructeur de recopie
}

void Joueur::Initialise(int numero, int argent, std::string pseudo, std::vector<Carte*> main)
{
  
}

void Joueur::Miser(int mise)
{
  
}

void Joueur::Pioche()
{
  
}
