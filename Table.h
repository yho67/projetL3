#ifndef Table_h
#define Table_h

#include <iostream>
#include <vector>
#include "Carte.h"
#include "Deck.h"
#include "Joueur.h"

// ---un objet "table" --> arguments : joueurs (tableau de pointeurs sur joueurs), mises (tableau des mises), mainbanque (tableau de pointeurs sur des objets cartes), 
//                         méthodes :   Pioche (pioche une carte du deck et l'ajoute à mainbanque. Si total mainbanque>21, on regarde s'il a un as, sinon perdu), paye (on modifie la somme d'argent du joueur).
//

class Joueur; //juste pour lui dire que la classe joueur existe

class Table
{
  	private:
  	Joueur m_tabjoueur[6]; // tableau de Joueurs. L'indice dans le tableau correspond au numéro du joueur. On met 6 cases car il peut y avoir un maximum de 6 joueurs.
  	std::vector<int> m_tabmise; // le tableau des mises des joueurs (pour un joueur : indice dans tabjoueur <-> indice dans tabmise
  	std::vector<Carte*> m_main_banque; //les cartes que le croupier a sur la table
  
  	public:
  	Table(); //constructeur par défaut 
	Table(Joueur tabjoueur[], std::vector<int> tabmise, std::vector<Carte*> main_banque); //constructeur
	~Table(); //destructeur
	Table(Table&); //constructeur de recopie

	//accesseur
	Joueur* GetTabJoueur(){return m_tabjoueur;}
	std::vector<int> GetTabMise(){return m_tabmise;}
	std::vector<Carte*> GetMainBanque(){return m_main_banque;}

	//mutateur
  	//on ne met pas de SetTabJoueur car on va avoir des méthode AjouterJoueur et EnleverJoueur
  	void SetTabMise(std::vector<int> tabmise){m_tabmise = tabmise;}
  	void SetMain(std::vector<Carte*> main_banque){m_main_banque = main_banque;}

	// méthodes particulières
	void Initialise(Joueur tabjoueur[], std::vector<int> tabmise, std::vector<Carte*> main_banque);
	void Paye(Joueur& joueur);
	void ModifMiseJoueur(int numero_joueur, int mise);
	void Pioche();
	void AjouterJoueur(Joueur joueur);
	void EnleveJoueur(int numeroJoueur);
  
  
  
};








#endif
