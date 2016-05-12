#include "Joueur.h"

#include <iostream>
#include <vector>


#include "Table.h"

using namespace std;

Joueur::Joueur()
{
  //constructeur par défaut 
	m_numero = -1; // on l'initialise comme un siège vide si rien de précisé.
  	m_argent = 0;
  	m_pseudo = ""; //les cartes que le joueur a sur la table
}

Joueur::Joueur(int numero, int argent, std::string pseudo, std::vector<Carte*> main)
{
  //constructeur
	m_numero = numero;
	m_argent = argent;
	m_pseudo = pseudo;
	m_main = main;
}

Joueur::~Joueur()
{
  //destructeur
}

Joueur::Joueur(Joueur &joueur)
{
  //constructeur de recopie
	m_numero = joueur.GetNumero();
	m_argent = joueur.GetArgent();
	m_pseudo = joueur.GetPseudo();
	m_main = joueur.GetMain(); //les vecteurs ont un système de copie efficace
}

void Joueur::Initialise(int numero, int argent, std::string pseudo, std::vector<Carte*> main)
{
	m_numero = numero;
	m_argent = argent;
	m_pseudo = pseudo;
	m_main = main;
}

void Joueur::Miser(int mise, Table* table)
{
	// on vérifie d'abord qu'on ne mise pas plus que l'argent que l'on a ou une somme négative
	if(mise>m_argent)
	{
		cout<<"Pas assez d'argent pour miser cette somme"<<endl;
	}
	else if(mise<0) 
	{
		cout<<"On ne peut pas miser une somme negative"<<endl;
	}
	else
	{
		//si tout est bon, on baisse l'argent du joueur et on enregistre sa mise;
		m_argent -= mise;
		table->ModifMiseJoueur(m_numero, mise); //on enregistre sa mise supplémentaire dans la table des mises
	}
}
void Joueur::AfficheMain()
{
	for(int i=0; i<m_main.size();i++)
	{
		cout<<m_main[i]->GetNumero()<<" "<<m_main[i]->GetCouleur()<<"  ||  ";
	}
	cout<<endl;
}

void Joueur::Pioche(Deck* deck, Table* table)
{
	Carte* new_carte = deck->Piocher(); // pointeur sur la nouvelle carte qu'on a tiré
	m_main.push_back(new_carte); // on l'ajoute a la main
	//on affiche la nouvelle main puis on regarde si on a dépassé la valeur autorisé.
	AfficheMain();
	int valeur_main = 0;
	bool modif_as = false;
	for(int i=0; i<m_main.size();i++)
	{
		valeur_main+=m_main[i]->GetValeur(); 
	}
	//si valeur_main dépasse 21, on regarde si on a un as
	if(valeur_main>21)
	{
		for(int i=0; i<m_main.size();i++)
		{
		//S'il a un as qui vaut 11, on change sa valeur et on sort de la boucle (modifier un seul as suffit)
			if(m_main[i]->GetValeur()==11)
			{
				m_main[i]->ChangeValeurAs(1);
				modif_as=true;
				break;
			}
		}
		if(modif_as) //si on a modifié un as, on est toujours dans le game
		{
			cout<<"Votre main a une valeur de "<<valeur_main<<endl;
		}
		else // si on a pas modifié l'as, on a dépassé 21 irrémédiablement
		{
			cout<<"Votre main a une valeur de "<<valeur_main<<endl;
			cout<<"Perdu !"<<endl;
			table->ModifMiseJoueur(m_numero, -1); // on remet la mise du joueur a 0;
		}
	}
}




