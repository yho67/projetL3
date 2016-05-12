#include "Table.h"

#include <iostream>
#include <vector>

#include "Table.h"



using namespace std;

Table::Table()
{
  //constructeur par défaut 
}

Table::Table(Joueur tabjoueur[], std::vector<int> tabmise, std::vector<Carte*> main_banque)
{
  //constructeur
}

Table::~Table()
{
  //destructeur
}

Table::Table(Table &table)
{
  //constructeur de recopie
}

void Table::Initialise(Joueur tabjoueur[], std::vector<int> tabmise, std::vector<Carte*> main_banque)
{
	
}

void Table::Paye(Joueur& joueur)
{
	// on connait le numéro du joueur qui est dans sa classe, ce qui donne son indice dans la table de mise également. Donc on peut modifier l'argent du joueur et la table de mise.
}

void Table::ModifMiseJoueur(int numero_joueur, int mise)
{
	
}

void Table::Pioche()
{
	// ajoute une carte à la main du croupier.
}

void Table::AjouterJoueur(Joueur joueur)
{
	
}

void Table::EnleveJoueur(int numeroJoueur)
{
	
}

