#ifndef Joueur_h
#define Joueur_h

#include <iostream>
#include <vector>
#include <string>
#include "Carte.h"
#include "Deck.h"
#include "Participant.h"

//---un objet "joueur" --> arguments : numéro, pseudo, main (tableau de pointeurs sur des objets cartes), argent
//			 méthodes : miser (diminue l'argent du jouer et modifie le tableau des mises de l'objet table), Pioche (pioche une carte du deck et l'ajoute à sa main. Si total main>21, on regarde s'il a un as, sinon, remise de mise à 0 dans tableau des mises)

class Joueur : public Participant
{
  	protected:
	//m_main et m_ptable (pointeur sur la table) existe par l'héritage;
  	int m_numero; //son identifiant pour le programme -> corrspond a l'indice de son pointeur dans le tableau tabjoueur de la classe table et au tableau tabmise. S'il vaut -1, le joueur est "vide" (siège vide).
  	int m_argent;
  	std::string m_pseudo;
  	
  
  	public:
  	Joueur(); //constructeur par défaut
	Joueur(int numero, int argent, std::string pseudo, std::vector<Carte*> main, Table* ptable); //constructeur
	Joueur(Joueur const& joueur); //constructeur de recopie

	//accesseur
	//GetMain et GetPtable existe par heritage
	int GetNumero(){return m_numero;}
	int GetArgent(){return m_argent;}
	std::string GetPseudo(){return m_pseudo;}

	//mutateur
	//SetTable et SetMain existe par héritage
	void SetNumero(int numero){m_numero = numero;}
 	void SetArgent(int argent){m_argent = argent;}
  	void SetPseudo(std::string pseudo){m_pseudo = pseudo;}


	// méthodes particulières
	//Pioche(Deck* deck); AfficheMain(); Perdu(int valeur_main) existent par héritage

	void Initialise(int numero, int argent, std::string pseudo, std::vector<Carte*> main, Table* ptable);
	void Miser(int mise, Table* table);
	void Perdu(int valeur_main); // on va juste ajouter la modification des mises lorsque le joueur perd
  
};








#endif
