#include "Deck.h"
#include <iostream>
#include <vector>

using namespace std;

Deck::Deck()
{
 //constructeur par défaut (initialise nombre cartes à 0 et le vecteur est déjà vide vecteur vide)
m_nombrecartes=0;
}

Deck::Deck(int nombrecartes, vector<Carte*> cartes_restantes)
{
 //constructeur
m_nombrecartes = nombrecartes;
m_cartesrestantes = cartes_restantes;
}

Deck::~Deck() 
{
//destructeur
}

Deck::Deck(Deck &) 
{
//constructeur de recopie
}

void Deck::Initialise(int nombrecartes, vector<Carte*> cartesrestantes)
{
m_nombrecartes = nombrecartes;
m_cartesrestantes = cartesrestantes;
return;
}

void Deck::Melanger()
{
// on va modifier aleatoirement l'ordre des cartes
// pour ça il faut connaître le nombre de cartes restantes, et : [1, 2, 3, 4] --> [3, 2, 4, 1]
}

Carte* Deck::Piocher()
{
// on va se servir de vector.back() pour récupérer le dernier élément puis vector.pop_back()
	Carte* p = m_cartesrestantes.back();
	m_cartesrestantes.pop_back();
	m_nombrecartes -= 1;
	return p;
}

