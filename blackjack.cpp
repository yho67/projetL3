//----------------------------ne pas oublier--------------------------------
//
//pouvoir personnaliser le nombre de joueur max, l'argent de départ (constructeur par défaut), nombre de deck utilisé, grâce à des fichiers.
//variable "continue", dont on passe le pointeur à la méthode joueur (puis perdu) pour savoir si on peut continuer de piocher
//2 test pour valeur optimal : un avec paquet tjrs plein, l'autre avec le aquet qu'on vide a chaque fois (on remplit s'il reste 10 cartes ou moins)
//mettre la main des joueurs qui n'ont pas gagné (pas d'appel Table.Paye pour eux ET qui n'ont pas dépassé 21) à vide
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

// -----------------------------------------LIRE LE README---------------------------------------------------------
 
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
			while(player.GetValeurMain()<14 && !perdu) // si on est a 14 ou plus on s'arrête
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
		ofstream proba("./probaMonteCarlo2.txt");
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
				if(deck.GetNombreCartes()<15)
				{
					deck = deck_default;
					deck.Melanger();
				}
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
		cout<<"seuil optimal est "<<seuil_optimal+1<<" avec "<<max_victoire<< " pour "<<nbre_partie<<" jouée."<<endl;
		proba<<"seuil optimal est "<<seuil_optimal+1<<" avec "<<max_victoire<< " pour "<<nbre_partie<<" jouée."<<endl;
		proba.close();
		break;
	}

	case 3  :
	{
		//methode baysienne : on veut savoir si l'on doit piocher, connaissant son score actuel
		// on va construire un tableau : indice = score avant de dépasser 21 ; dans la case = nbre de fois ou dépassé 21 en ayant ce score en dernier
		//et un autre ou indice = pareil et après le nombre de fois ou on a pu continué
				
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

		//on ouvre le fichier dans lequel on va écrire nos stats
		ofstream proba("./statsBayesienne.txt");
		if(!proba)
		{
			cout<<"Impossible d'ouvrir le fichier statsBayesienne.txt"<<endl;
			return 0;	
		}
		
		vector<int>statsperdu(22, 0);
		vector<int>statscontinuer(22,0);
		for(int i=0;i<nbre_partie;i++)
		{
			// on initialise la main à vide au cas où.
			player.ReinitialiseMain();
			deck = deck_default;
			deck.Melanger();
			bool perdu = false;
			int valeur_en_cours = 0;
			while(!perdu &&player.CalculValeurMain()<21)
			{
				player.Pioche(&deck);
				perdu = player.Perdu();
				if(!perdu)
				{
					statscontinuer[valeur_en_cours] +=1;
					valeur_en_cours = player.CalculValeurMain();
				}
			}
			// on s'arrête forcément après avoir dépasé 21, reste à regarder la valeur de valeur_en_cours
			statsperdu[valeur_en_cours] +=1;
		}
		double proba_condi = 0.0;
		for(int i=0; i<22; i++)
		{
			//on enregistre le tout dans le fichier
			if(statsperdu[i]+statscontinuer[i] != 0)
			{
				proba_condi = (double)statsperdu[i]/(statsperdu[i]+statscontinuer[i]);
			}	
			else
			{
				proba_condi = 0.0;
			}
			proba<<i<<"  "<<statsperdu[i]<<"  "<<statscontinuer[i]<<"  "<<proba_condi<<endl;
		}
		
		proba.close();
		
		break;
	}

	case 4  :
	{
		//on s'intéresse cette fois au seuil optimal, connaissant la première carte du joueur et celle du croupier
		//on va alors créer un tableau à double entrée répertoriant le seuil optimal:
		//      croupier  As  2  3  4  5  6  
		//joueur
		//  As            15 16 ...
		//  1             16 14 ...
		//  2              .  .  .
		//  3              .  .    .
		//  4              .  .      .
		
		// on va utiliser la même technique que dans le case2 (copier coller) sauf qu'on va fixer la première carte du joueur et du croupier, et qu'on va devoir enlever ces cartes du deck avant de le mélanger à chaque fois.

		
		//on commence par ouvrir le fichier option3 qui contient le nombre de parties que l'on veut simuler pour chaque seuil
		ifstream option3("./option3.txt");  

		if(!option3)
		{
			//si on arrive pas a ouvrir le fichier on sort du prog
			cout<<"Impossible de trouver le fichier option3"<<endl;
			return 0;
		}
		int nbre_partie;
		option3 >> nbre_partie;
		option3.close();

		//on ouvre le fichier dans lequel on va écrire notre seuil
		ofstream proba("./probaSeuilConditionnel.txt");
		if(!proba)
		{
			cout<<"Impossible d'ouvrir le fichier probaSeuilConditionnel.txt"<<endl;
			return 0;	
		}
		//créons notre tableau qu'on enregistrera a la fin dans un fichier
		int seuil_conditionnel [14][14];
		for(int x = 0; x<14; x++)
		{
			seuil_conditionnel[x][0] = x;
		}
		for(int y = 0; y<14; y++)
		{
			seuil_conditionnel[0][y] = y;
		}
		//on fixe les premières cartes
		for(int x=1;x<14;x++)
		{
			for(int y=1;y<14;y++)
			{

				int max_victoire = 0;
				int seuil_optimal = 0;
				for(int j=1;j<22;j++) //j sera notre seuil
				{
					int nbre_gagne = 0;
					int nbre_perdu = 0;
					int nbre_egalite = 0;
					for(int i=0;i<nbre_partie;i++)
					{
						// on initialise la main à vide au cas où.
						player.ReinitialiseMain();
						deck = deck_default;
						
						Carte* premiere_carte_croupier = deck.GetCartesRestantes()[x-1];
						Carte* premiere_carte_joueur = deck.GetCartesRestantes()[y+12]; //pas de la même couleur pour pas de problèmes si même numéro ( y+12 = (y-1) + 13 -> changement de couleur)
						//on les enlève du deck ces cartes fixées
						vector<Carte*> cartes = deck.GetCartesRestantes();
						cartes.erase(cartes.begin()+(x-1), cartes.begin()+(x));
						cartes.erase(cartes.begin()+(y+12), cartes.begin()+(y+13));
						deck.SetCartesRestantes(cartes);
						
						//on donne au joueur sa première carte :
						vector<Carte*> main_joueur;
						main_joueur.push_back(premiere_carte_joueur); 
						player.SetMain(main_joueur);
						
						//on reprend le cours normal du programme
						deck.Melanger();
						bool perdu = false;
						while(player.GetValeurMain()<j && !perdu) 
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
							//on donne au croupier sa première carte
							vector<Carte*> main_croupier;
							main_croupier.push_back(premiere_carte_croupier); 
							croupier.SetMain(main_croupier);
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
					
					//on détermine quel seuil est optimal
					if(max_victoire<nbre_gagne)
					{
						max_victoire=nbre_gagne;
						seuil_optimal = j;
					}	
				}
				//on enregistre le seuil optimal conditionnel dans le tableau
				seuil_conditionnel[x][y] = seuil_optimal;
			}
		}
		// enfin on écrit toute danss le fichier
		for(int x=0;x<14;x++)
		{
			for(int y=0;y<14;y++)
			{
				proba<<seuil_conditionnel[y][x]<<"            ";
			}
			proba<<endl;
		}
		proba<<"test avec "<<nbre_partie<<" parties jouées par seuil"<<endl;
		proba.close();
		
		break;
	}

	default : 
		cout<<"cete option n'existe pas"<<endl;
		

}//fin du switch
	


	return 0;
}











