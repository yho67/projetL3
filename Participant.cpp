#include "Participant.h"

#include <iostream>
#include <vector>

using namespace std;

Participant::Participant()
{
  //constructeur par défaut : rien à mettre
}

Participant::Participant(std::vector<Carte*> main, Table* ptable) : m_main(main), m_ptable(ptable)
{
  //constructeur
}


Participant::Participant(Participant &participant)
{
  //constructeur de recopie
	m_ptable = participant.GetPtable();
	m_main = participant.GetMain(); //les vecteurs ont un système de copie efficace
}

void Participant::AfficheMain()
{
	for(int i=0; i<m_main.size();i++)
	{
		cout<<m_main[i]->GetNumero()<<" "<<m_main[i]->GetCouleur()<<"  ||  ";
	}
	cout<<endl;
}

void Participant::Pioche(Deck* deck)
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
		if(!modif_as)// si on a pas modifié l'as, on a dépassé 21 irrémédiablement
		{
			this->Perdu(valeur_main);	
		}
	}
}

void Participant::Perdu(int valeur_main)
{
	cout<<"Cette main a une valeur de "<<valeur_main<<endl;
	cout<<"Perdu !"<<endl;
	// on remet les as qu'il a en main a une valeur de 11
	for(int i=0; i<m_main.size();i++)
	{
		m_main[i]->ChangeValeurAs(11);;
	}
}


