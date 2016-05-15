#ifndef Carte_h
#define Carte_h

#include <iostream>
#include <string>

// ---un objet "carte" --> arguments : le numéro, la couleur, la valeur
//                      méthodes : valeuras : si la carte est un as, alors on change la valeur en 1 au lieu de 11
class Carte
{
	private:
	int m_numero, m_valeur;
	std::string m_symbol;
	std::string m_couleur;

	public:
	Carte(); //constructeur par défaut (initialise num et valeurs à 0 et couleurs nulle)
	Carte(int numero, std::string couleur); //constructeur
	~Carte(); //destructeur
	Carte(Carte &); //constructeur de recopie

	//accesseur
	int GetNumero(){return m_numero;}
	int GetValeur(){return m_valeur;}
	std::string GetSymbol(){return m_symbol;}
	std::string GetCouleur(){return m_couleur;}

	//mutateur
	void SetNumero(int numero){m_numero = numero;} // inutile ?
	void SetValeur(int valeur){m_valeur = valeur;}
	void SetSymbol(std::string symbol){m_symbol = symbol;}
	void SetCouleur(std::string couleur){m_couleur = couleur;}

	// méthodes particulières
	void ChangeValeurAs(int valeur);
	void Initialise(int numero, std::string couleur);
};

#endif
