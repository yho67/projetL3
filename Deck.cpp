#include "Deck.h"

#include <iostream>
#include <vector>
#include <cstdlib>
#include "Carte.h"

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

Deck::Deck(Deck & D) 
{
//constructeur de recopie
	m_nombrecartes = D.GetNombreCartes();
	m_cartesrestantes = D.GetCartesRestantes(); //les vecteurs présentent déjà une méthode de copie efficace
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
// pour ça il faut commencer par pouvoir faire : [1, 2, 3, 4] --> [3, 2, 4, 1]

	//on va créer un vecteur contenant les nombres de 0 à m_nombrescartes-1
	//on va générer un nombre aléatoire A allant de 0 à m_nombrescartes-1
	//puis retirer l'entrée numéro A du vecteur
	//ça va nous permettre de ne faire tourner le générateur de hasard que m_nombrescartes-1 fois pour construire un vecteur contenant tous les nombres entre 0 et m_nombrescartes-1 placés aléatoirement
	
	int n = m_nombrecartes;
	vector<int> vecteur_ordonne; // le vecteur contenant les nombres dans l'ordre
	for(int i =0; i<n;i++)
	{
		vecteur_ordonne.push_back(i);
	}
	
	vector<int> vecteur_ordre_alea;
	for(int i=0; i<m_nombrecartes-1;i++)
	{	
		 
		int alea = rand()%n;// on prend un nombre aléatoire entre 0 et le nombre d'entrées restantes dans vecteur_ordonne-1
		vecteur_ordre_alea.push_back(vecteur_ordonne[alea]); // on met le nombre de vecteur_ordonne correspondant à l'indice alea dans vecteur_ordre_alea en dernière position
		vecteur_ordonne.erase(vecteur_ordonne.begin()+(alea), vecteur_ordonne.begin()+(alea+1)); // enfin on efface l'entrée
		n-=1;
	}
	vecteur_ordre_alea.push_back(vecteur_ordonne[0]);//on ajoute le dernier restant de vecteur_ordonne
	
	// on a maintenant un vecteur qui contient tous les entiers de 0 à 51 dans le désordre

	// construisons maintenant le nouveau vecteur cartes restantes avec un ordre aléatoire
	vector<Carte*> new_cartesrestantes;
	
	for(int i =0; i<m_nombrecartes;i++)
	{
		new_cartesrestantes.push_back(m_cartesrestantes[vecteur_ordre_alea[i]]);
	}
	
	//enfin on remplace le précédent m_cartesrestantes par celui mélangé
	m_cartesrestantes = new_cartesrestantes;
	
}

Carte* Deck::Piocher()
{
// on va se servir de vector.back() pour récupérer le dernier élément puis vector.pop_back()
	Carte* p = m_cartesrestantes.back();
	m_cartesrestantes.pop_back();
	m_nombrecartes -= 1;
	return p;
}

