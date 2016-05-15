// on va commencer par modéliser un jeu de cartes avec un joueur (nous) et un croupier (I.A)
// on reste en terminal.
// Les informations à transmettre : les cartes en jeu du joueur / les cartes en jeu du croupier / la mise du joueur / la somme total d'argent du joueur.
// Le joueur peut continuer de piocher autant qu'il veut sauf s'il atteint 22 ou plus.
// le croupier s'arrête dès qu'il atteint 17 ou plus.
// celui qui a la plus grosse somme des deux remporte la manche. Le joueur peut choisir de continuer ou de quitter la table.

// ------ 2eme étape -----
// on va essayer de voir pour le jouer quel est le nombre qui s'il s'y arrête lui offre la plus grande chance de victoire. On simulera beaucoup de parties pour ça.

//------- 3eme étape ------
// on va cette fois tenir compte des cartes précédemment tirées pour s'arrêter ou non de jouer.
// on va faire un tableau de probabilités (si score de X -> Y de chance de gagner ).
// on utilisera alors ce tableau de probabilités pour estimer si l'on doit continuer ou non  + le nombre précédemment trouvé : (O.5 + Y)/2 > 0.5 --> continue sinon non.

//------- 4eme etape --------
// prendre en compte la mise du joueur dans les probabilités de la banque





//----------------------------ne pas oublier--------------------------------
//
//pouvoir personnaliser le nombre de joueur max, l'argent de départ (constructeur par défaut), nombre de deck utilisé, grâce à des fichiers.
//variable "continue", dont on passe le pointeur à la méthode joueur (puis perdu) pour savoir si on peut continuer de piocher
//2 test pour valeur optimal : un avec paquet tjrs plein, l'autre avec le aquet qu'on vide a chaque fois (on remplit s'il reste 10 cartes ou moins)
//mettre la main des joueurs qui n'ont pas gagné (pas d'appel Table.Paye pour eux ET qui n'ont pas dépassé 21) à 21
#include <iostream>
#include <string>
#include <vector> 
#include <cstdlib>
#include <ctime>

#include "Participant.h"
#include "Carte.h"
#include "Deck.h" 
#include "Joueur.h"
#include "Table.h"

 
using namespace std;

int main(int argc, char *argv[])
{
	//notre programme utilise de l'aléatoire, il faut donc initialiser srand()
	srand(time(NULL));
	
	// on va créer un tableau qui contient nos 52 cartes. (Ce n'est pas le deck ! juste la liste des cartes qu'on utilise).
	Carte tabCartes[52];
	for(int i=0; i<13;i++)
	{
		tabCartes[i].Initialise(i+1, "coeur");
	}
	for(int i=0; i<13;i++)
	{
		tabCartes[i+13].Initialise(i+1, "carreau");
	}
	for(int i=0; i<13;i++)
	{
		tabCartes[i+26].Initialise(i+1, "pique");
	}
	for(int i=0; i<13;i++)
	{
		tabCartes[i+39].Initialise(i+1, "trefle");
	}

	//on crée maintenant un vecteur de pointeurs sur ces cartes dont on se servira pour créer le deck
	vector<Carte*> VectPointeurCartes;
	for(int i =0; i<52;i++)
	{
		VectPointeurCartes.push_back(&tabCartes[i]);
		// /!\ pour appeler les méthodes il faudra alors faire VectPointeurCartes[i]->GetNumero()
	}
	
	Deck deck_default(52, VectPointeurCartes); // paquet qu'on ne modifie pas
	Deck deck(52, VectPointeurCartes);
	//on a créé notre Deck. Passons aux joueurs.
	vector<Carte*> main;
	Table table(1);
	Joueur player(0, 500, "yho67", main, &table);
	
	
	
	for(int i=0;i<10;i++)
	{
		// on initialise la main à vide au cas où.
		player.SetMain(main);
		deck = deck_default;
		deck.Melanger();
		bool perdu = false;
		while(player.ValeurMain()<16 && !perdu) // si on est a 17 ou plus on s'arrête
		{
			
			player.Pioche(&deck);
			perdu = player.Perdu();
		}
		if(perdu)
		{
			cout<<"perdu"<<endl;
		}
		else
		{
			cout<<"Voyons la banque"<<endl;
		}
		
	}


	


	


	return 0;
}











