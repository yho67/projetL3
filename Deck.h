#ifndef Deck_h
#define Deck_h

#include <iostream>
#include <vector> 
#include "Carte.h"


// ---un objet "deck" --> arguments : nombre de cartes restantes, tableau (vecteur) des cartes restantes (pointeurs sur l'objet carte)
//                     méthodes : piocher (donne la carte la plus à droite du tableau des cartes restantes et modifie le nombre de cartes), melanger (modifie aléatoirement l'ordre des cartes dans le tableau)
//

class Deck
{
	private:
	int m_nombrecartes;
	std::vector<Carte*> m_cartesrestantes; //Vecteur de pointeurs sur des objets cartes
	

	public:
	Deck(); //constructeur par défaut (initialise nombre cartes à 0 et un vecteur vide)
	Deck(int nombrecartes, std::vector<Carte*> cartes_restantes); //constructeur
	~Deck(); //destructeur
	Deck(Deck &); //constructeur de recopie

	//accesseur
	int GetNombreCartes(){return m_nombrecartes;}
	std::vector<Carte*> GetCartesRestantes(){return m_cartesrestantes;}

	//mutateur
	void SetNombreCartes(int nombrecartes){m_nombrecartes = nombrecartes;}
	void SetCartesRestantes(std::vector<Carte*> cartesrestantes){m_cartesrestantes = cartesrestantes;}
	

	// méthodes particulières
	void Initialise(int nombrecartes, std::vector<Carte*> cartesrestantes);
	void Melanger();
	Carte* Piocher();
	void Affiche();
	

};


#endif
