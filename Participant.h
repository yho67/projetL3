#ifndef Participant_h
#define Participant_h

#include <iostream>
#include <vector>
#include <string>
#include "Carte.h"
#include "Deck.h"

class Table; // Juste pour lui dire que le type Table existe (forward declaration)

class Participant
{
  	protected:
	Table* m_ptable; //pointeur sur table, pour pouvoir interagir avec (classe fille)
  	std::vector<Carte*> m_main; //les cartes que le participant a sur la table
  
  	public:
  	Participant(); //constructeur par défaut
	Participant(std::vector<Carte*> main, Table* ptable); //constructeur
	Participant(Participant&); //constructeur de recopie

	//accesseur
	Table* GetPtable(){return m_ptable;}
	std::vector<Carte*> GetMain(){return m_main;}

	//mutateur
	void SetTable(Table* ptable){m_ptable = ptable;}
  	void SetMain(std::vector<Carte*> main){m_main = main;}

	// méthodes particulières
	void Pioche(Deck* deck);
	void AfficheMain();
	void Perdu(int valeur_main);
  
  
  
};

#endif
