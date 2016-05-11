#ifndef Table_h
#define Table_h

#include <iostream>
#include <vector>
#include <string>
#include "Carte.h"
#include "Deck.h"
#include "Joueur.h"

class Table
{
  private:
  
  std::vector<int> m_tabjoueurs; // on a attribué un numéro aux joueurs dont on va se servir ici pour les différencier
  std::vector<int> m_tabmise; // le tableau des mises des joueurs (l'indice du vecteur correspond au numéro du joueur)
  std::vector<Carte*> m_main_banque; //les cartes que le croupier a sur la table
  
  public:
  Table(); //constructeur par défaut (initialise nombre cartes à 0 et un vecteur vide)
	Table(int numero, int argent, std::string pseudo, std::vector<Carte*> main); //constructeur
	~Table(); //destructeur
	Table(Table &); //constructeur de recopie
	//accesseur
	int GetNumero(){return m_numero;}
	int GetArgent(){return m_argent;}
	std::string GetPseudo(){return m_pseudo;}
	std::vector<Carte*> GetMain(){return m_main;}
	//mutateur
  void SetArgent(int argent){m_argent = argent;}
  void SetPseudo(std::string pseudo){m_pseudo = pseudo;}
  void SetMain(std::vector main){m_main = main;}
	// méthodes particulières
	void Initialise(int numero, int argent, std::string pseudo, std::vector<Carte*> main);
	void Miser(int mise);
	void Pioche();
  
  
  
};








#endif