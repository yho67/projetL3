# projetL3
création d'un jeu de blackjack
https://github.com/yho67/projetL3

pour la compilation : compiler tous les fichiers de classe, puis le programme blackjack.cpp: (attention, pour Carte.cpp il faut utilise la norme c++11 :)
g++ -std=c++11 -c Carte.cpp
g++ -c Deck.cpp
g++ -c Participant.cpp
g++ -c Joueur.cpp
g++ -c Table.cpp
g++ Carte.o Deck.o Participant.o Joueur.o Table.o blackjack.cpp -o blackjack.exe


le programme se lance en  console : ./blackjack.exe -option
option du jeu de blackack :

	1 : simule un nombre de partie à préciser dans le fichier option1.txt, que l'on peut voir sur la console.

	2 : simule un nombre de partie (de préférence beacoup plus important), à préciser dans le fichier option2.txt, sans le visuel. On modifie progressivement ici le seuil auquel s'arrête le joueur, pour connaitre les probabilités de gagner en fonction de ce seuil, et trouver le seuil qui permet de gagner le plus de parties. Les résultats sont enregistrés dans le fichier probaMonteCarlo.txt

	3 : permet d'obtenir les probabilités de dépasser 21 si l'on pioche, connaissant notre score actuel. Le nombre de parties simulées est le même que pour l'option 2, à régler dans le fichier option2.txt donc. Les résultats sont donnés dans le fichier statsBayesienne.txt, la dernière colonne donne les probabilités en fonction du score de la première colonne.
	
	4 : permet de calculer le seuil optimal en connaissant la première carte du croupier et celle du joueur. Le nombre de partie a effectuer par seuil est à préciser dans le fichier option3.txt. Résultats donnés sous forme de tableau dans le fichier probaSeuilConditionnel.txt.


#INFO : comme les programmes peuvent prendre un certain temps (notamment l'option 4 qui a mis plusieurs heures chez moi avec un bonne puissance de calcul), je les ai inclus dans l'archive.
