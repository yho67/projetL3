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


// ------------------1ere étape --------------------
// a programmer :
// ---un objet "carte" --> arguments : le numéro, la couleur, la valeur
//                      méthodes : valeuras : si la carte est un as, alors on change la valeur en 1 au lieu de 11
//
// ---un objet "deck" --> arguments : nombre de cartes restantes, tableau des cartes restantes (pointeurs sur l'objet carte)
//                     méthodes : piocher (donne la carte la plus à gauche du tableau des cartes restantes et modifie le nombre de cartes), melanger (modifie aléatoirement l'ordre des cartes dans le tableau)
//
// ---un objet "joueur" --> arguments : numéro, pseudo, main (tableau de pointeurs sur des objets cartes), argent
//			 méthodes : miser (diminue l'argent du jouer et modifie le tableau des mises de l'objet table), encore (pioche une carte du deck et l'ajoute à sa main. Si total main>21, on regarde s'il a un as, sinon, remise de mise à 0 dans tableau des mises)
//
// ---un objet "table" --> arguments : joueurs (tableau de joueurs), mises (tableau des mises), mainbanque (tableau de pointeurs sur des objets cartes), 
//                         méthodes :   miser, encore (pioche une carte du deck et l'ajoute à mainbanque. Si total mainbanque>21, on regarde s'il a un as, sinon perdu), paye (on modifie la somme d'argent du joueur).
//
//
//


//----------------------------ne pas oublier--------------------------------
// -- 

#include <iostream>
#include <string>

#include "Carte.h" //classe carte
 
using namespace std;

int main()
{
	Carte test(1, "pique");
	cout<<test.GetNumero()<<"  "<<test.GetValeur()<<endl;
	string a=test.GetCouleur();
	cout<<a<<endl;
	test.ChangeValeurAs();
	cout<<test.GetValeur()<<endl;
	return 0;
}











