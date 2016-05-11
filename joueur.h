#ifndef Joueur_h
#define Joueur_h

#include <iostream>
#include <vector>
#include <string>
#include "Carte.h"
#include "Deck.h"

class Joueur
{
  private:
  int m_numero; //son identifiant pour le programme
  int m_argent;
  std::string m_pseudo;
  std::vector<Carte*> m_main; //les cartes que le joueur a sur la table
  
  public:
  Joueur(); //constructeur par défaut (initialise nombre cartes à 0 et un vecteur vide)
	Joueur(int numero, int argent, std::string pseudo, std::vector<Carte*> main); //constructeur
	~Joueur(); //destructeur
	Joueur(Joueur &); //constructeur de recopie
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