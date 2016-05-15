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
}

int Participant::ValeurMain()
{
	int valeur_main = 0;
	for(int i=0; i<m_main.size();i++)
	{
		valeur_main+=m_main[i]->GetValeur(); 
	}
	return valeur_main;
}

bool Participant::Perdu()
{

	bool modif_as = false;
	bool perdu = false;
	//si valeur_main dépasse 21, on regarde si on a un as
	if(ValeurMain()>21)
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
			perdu = true;
		}
	}
	cout<<"Cette main a une valeur de "<<ValeurMain()<<endl;
	// on remet les as qu'il a en main a une valeur de 11
	//si c'est perdu on remet sa main à vide et on remet les as qu'il avait en main à une valeur de 11
	if(perdu)
	{
		for(int i=0; i<m_main.size();i++)
		{
			m_main[i]->ChangeValeurAs(11);;
		}
		std::vector<Carte*> vide; 
		SetMain(vide);
	}
	return perdu;
}


