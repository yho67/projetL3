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
#include <sstream>
#include <string>
#include <vector> 
#include <cstdlib>
#include <ctime>
#include <fstream>

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
	vector<Carte*> main_vide;
	Table table(1);

	Joueur player(0, 500, "yho67", main_vide, &table);
	Participant croupier(main_vide, &table);
	// notre programme va, dépendant de l'option avec lequel on l'appelle, effectuer divers actions
	// 1 : calcul du seuil optimal
	// 2 : bayesienne

	//l'option est passé en option au programme en mode console
	int option;
	istringstream convert(argv[1]); //on convertit la première option de string à int

	if ( !(convert >> option) )//on met le int converti dans option
		option = 0;//s'il y a eu un problème, on retourne 0
	
switch(option)
{
	case 0  :
		cout<<"pas d'options spécifiées"<<endl;
		break; 

	case 1  :
	{
		//visuel sur console de la simulation de poker a 1 joueur VS un croupier
		
		//on commence par ouvrir le fichier option1 qui contient le nombre de parties que l'on veut simuler
		ifstream option1("./option1.txt");  

		if(!option1)
		{
			//si on arrive pas a ouvrir le fichier on sort du prog
			cout<<"Impossible de trouver le fichier option1"<<endl;
			return 0;
		}
		int nbre_partie;
		option1 >> nbre_partie;
		option1.close();		
		
		for(int i=0;i<nbre_partie;i++)
		{
			
			// on initialise la main à vide au cas où.
			player.ReinitialiseMain();
			deck = deck_default;
			deck.Melanger();
			bool perdu = false;
			while(player.GetValeurMain()<16 && !perdu) // si on est a 17 ou plus on s'arrête
			{
				player.Pioche(&deck);
				player.AfficheMain();
				perdu = player.Perdu();
				cout<<"Cette main vaut "<< player.GetValeurMain()<<" points"<<endl;
			}
			if(perdu)
			{
				//le joueur perd
				cout<<endl;
				cout<<"perdu"<<endl;
			}
			else //----------- passons à la banque---------------
			{
				cout<<endl;
				cout<<"Voyons la banque"<<endl;cout<<endl;
				croupier.ReinitialiseMain();
				bool perdu_croupier = false;
				while(croupier.GetValeurMain()<17 && !perdu_croupier) // si on est a 17 ou plus on s'arrête
				{
					croupier.Pioche(&deck);
					croupier.AfficheMain();
					perdu_croupier = croupier.Perdu();
					cout<<"main du croupier vaut "<< croupier.GetValeurMain()<<" points"<<endl;
				}
				if(perdu_croupier)
				{
					// le joueur gagne
					cout<<endl;
					cout<<"le croupier a dépassé 21"<<endl;
					cout<<"gagné!"<<endl;
				}
				else //si le croupier n'a pas dépassé 21, on compare son score avec celui du joueur
				{
					cout<<endl;
					if(player.GetValeurMain()<croupier.GetValeurMain())
					{
						//le joueur perd
						cout<<"perdu"<<endl; 
					}
					else if(player.GetValeurMain()==croupier.GetValeurMain())
					{
						//egalite
						cout<<"egalite"<<endl;
					}
					else
					{
						//le joueur gagne
						cout<<"gagné !"<<endl; 
					}
				}
			}

			cout<<endl;
			cout<<"------------------------------------"<<endl; cout<<endl;		
		}
		break;
	}
	case 2:
	{
		//détermination du seuil optimal pour le joueur
		
		//on commence par ouvrir le fichier option2 qui contient le nombre de parties que l'on veut simuler pour chaque seuil
		ifstream option2("./option2.txt");  

		if(!option2)
		{
			//si on arrive pas a ouvrir le fichier on sort du prog
			cout<<"Impossible de trouver le fichier option2"<<endl;
			return 0;
		}
		int nbre_partie;
		option2 >> nbre_partie;
		option2.close();

		//on ouvre le fichier dans lequel on va écrire le nombre de partie gagné || perdu || egalite en fonction du seuil  (fichier de la forme : seuil  nbre_gagne  nbre_perdu  nbre_egalite)
		ofstream proba("./probaMonteCarlo.txt");
		if(!proba)
		{
			cout<<"Impossible d'ouvrir le fichier probaMonteCarlo.txt"<<endl;
			return 0;	
		}
		
		int max_victoire = 0;
		int seuil_optimal = 0;
		for(int j=1;j<22;j++) //j sera notre seuil
		{
			proba<<j<<" ";
			int nbre_gagne = 0;
			int nbre_perdu = 0;
			int nbre_egalite = 0;
			for(int i=0;i<nbre_partie;i++)
			{
				// on initialise la main à vide au cas où.
				player.ReinitialiseMain();
				deck = deck_default;
				deck.Melanger();
				bool perdu = false;
				while(player.GetValeurMain()<j && !perdu) // si on est a 17 ou plus on s'arrête
				{
					player.Pioche(&deck);
					perdu = player.Perdu();
				}
				if(perdu)
				{
					//le joueur perd
					nbre_perdu += 1;
				}
				else //----------- passons à la banque---------------
				{
					croupier.ReinitialiseMain();
					bool perdu_croupier = false;
					while(croupier.GetValeurMain()<17 && !perdu_croupier) // si on est a 17 ou plus on s'arrête
					{
						croupier.Pioche(&deck);
						perdu_croupier = croupier.Perdu();
					}
					if(perdu_croupier)
					{
						// le joueur gagne
						nbre_gagne += 1;
					}
					else //si le croupier n'a pas dépassé 21, on compare son score avec celui du joueur
					{
						if(player.GetValeurMain()<croupier.GetValeurMain())
						{
							//le joueur perd
							nbre_perdu += 1;
						}
						else if(player.GetValeurMain()==croupier.GetValeurMain())
						{
							//egalite
							nbre_egalite +=1;
						}
						else
						{
							//le joueur gagne
							nbre_gagne +=1;
						}
					}
				}
	
			}
			//on enregistre les nbres de defaites/victoires dans le fichier.
			proba<<nbre_gagne<<" "<<nbre_perdu<<" "<<nbre_egalite<<endl;
			//et on détermine quel seuil est optimal
			if(max_victoire<nbre_gagne)
			{
				max_victoire=nbre_gagne;
				seuil_optimal = j;
			}	
		}
		cout<<"seuil optimal est "<<seuil_optimal<<" avec "<<max_victoire<< " pour "<<nbre_partie<<" jouée."<<endl;
		proba<<"seuil optimal est "<<seuil_optimal<<" avec "<<max_victoire<< " pour "<<nbre_partie<<" jouée."<<endl;
		proba.close();
		break;
	}
	default : 
		cout<<"cete option n'existe pas"<<endl;

}//fin du switch
	


	return 0;
}











