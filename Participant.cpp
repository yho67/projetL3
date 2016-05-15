#include "Participant.h"

#include <iostream>
#include <vector>

using namespace std;

Participant::Participant()
{
  //constructeur par défaut : rien à mettre
}

Participant::Participant(std::vector<Carte*> main, Table* ptable) : m_main(main), m_ptable(ptable), m_valeur_main(0)
{
  //constructeur
}


Participant::Participant(Participant &participant)
{
  //constructeur de recopie
	m_ptable = participant.GetPtable();
	m_main = participant.GetMain(); //les vecteurs ont un système de copie efficace
	m_valeur_main = participant.GetValeurMain();
}

void Participant::AfficheMain()
{
	for(int i=0; i<m_main.size();i++)
	{
		cout<<m_main[i]->GetSymbol()<<" "<<m_main[i]->GetCouleur()<<"  ||  ";
	}
	cout<<endl;
}

void Participant::Pioche(Deck* deck)
{
	Carte* new_carte = deck->Piocher(); // pointeur sur la nouvelle carte qu'on a tiré
	m_main.push_back(new_carte); // on l'ajoute a la main
}

int Participant::CalculValeurMain()
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
	m_valeur_main = CalculValeurMain();
	//si valeur_main dépasse 21, on regarde si on a un as
	if(m_valeur_main>21)
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
	//on recalcule la valeur de la main après possible changement des as
	m_valeur_main = CalculValeurMain();
	// on remet les as qu'il a en main a une valeur de 11
	//si c'est perdu on remet sa main à vide et on remet les as qu'il avait en main à une valeur de 11
	return perdu;
}

void Participant::ReinitialiseMain()
{
	//on remet sa main à vide et on remet les as qu'il avait en main à une valeur de 11
	for(int i=0; i<m_main.size();i++)
	{
		m_main[i]->ChangeValeurAs(11);;
	}
	std::vector<Carte*> vide; 
	m_main = vide;
	m_valeur_main = 0;
	
}

