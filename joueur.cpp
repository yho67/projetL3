#include "Deck.h"
#include <iostream>
#include <vector>

using namespace std;

Joueur::Joueur()
{
  //constructeur par défaut (initialise nombre cartes à 0 et un vecteur vide)
}

Joueur::Joueur(int numero, int argent, std::string pseudo, std::vector<Carte*> main)
{
  //constructeur
}

Joueur::~Joueur()
{
  //destructeur
}

Joueur::Joueur::Joueur(Joueur &)
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
