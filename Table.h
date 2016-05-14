#ifndef Table_h
#define Table_h

#include <iostream>
#include <vector>
#include "Carte.h"
#include "Deck.h"
#include "Joueur.h"

// ---un objet "table" --> arguments : joueurs (tableau de pointeurs sur joueurs), mises (tableau des mises) 
//                         méthodes :   Pioche (pioche une carte du deck et l'ajoute à mainbanque. Si total mainbanque>21, on regarde s'il a un as, sinon perdu), paye (on modifie la somme d'argent du joueur).
//

class Table
{
  	private:
	int m_nbre_max_joueur;
  	std::vector<Joueur> m_tabjoueur; // tableau de Joueurs. L'indice dans le tableau correspond au numéro du joueur. std::vector<TypeCellule>(  w, TypeCellule( ParametreConstruction )
  	std::vector<int> m_tabmise; // le tableau des mises des joueurs (pour un joueur : indice dans tabjoueur <-> indice dans tabmise
  
  	public:
  	Table(); //constructeur par défaut 
	Table(int const nbre_max_joueur); //constructeur ; on n'initialise pas le tableau des joueurs, puisqu'on a les méthodes ajouterJoueur et EnleverJoueur pour ça.
	~Table(); //destructeur

	//accesseur
	std::vector<Joueur> GetTabJoueur(){return m_tabjoueur;}
	std::vector<int> GetTabMise(){return m_tabmise;}

	//mutateur
  	//on ne met pas de SetTabJoueur car on va avoir des méthode AjouterJoueur et EnleverJoueur
  	void SetTabMise(std::vector<int> tabmise){m_tabmise = tabmise;}

	// méthodes particulières
	void Paye(int numero_joueur, int multiplicateur = 1);
	void ModifMiseJoueur(int numero_joueur, int mise);
	Joueur* AjouterJoueur(); // on renvoie un pointeur sur le joueur qu'on a ajouté
	void EnleverJoueur(int numero_joueur);
  
};








#endif
