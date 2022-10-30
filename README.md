# Projet Quoridor

- [Sujet du projet](https://www.labri.fr/perso/renault/working/teaching/projets/2021-22-S6-C-Flood.php)

- [Page sur thor](https://thor.enseirb-matmeca.fr/ruby/projects/projetss6-flood)

(C): ABIBI Aymane, SOUFARY Farouk, ELBOUSTY Badreddine, NAAMI Anas

# Mode de compilation :

- make build : compile l'ensemble du projet 

- make install : déplace l'éxecutable server et alltests, ainsi que l'ensemble des bibliothèques
utilisées dans le server dans le répertoire install.

- make test : compile l'ensemble des fichiers tests.

- make clean : Supprime les éxecutables, les fichiers objets, et les bibliothèques utilisées dans le projet.

# Les tests :

- Les différentes fonctions utilisées dans ce projet sont testées avec des assert. 
L'éxecution de chaque fichier test, renvoie un "OK" à côté du nom de la fonction testée, si cette fonction renvoie le résultat attendu.

- Le fichiers alltests.c englobe les tests des différentes fonction utilisées dans ce projet.

# Éxecution :

- Après compilation du projet. Le serveur prend des options dans la ligne du commande :
 * L'option -m permet de spécifier la largeur du plateau de jeu (ex -m 10).
 * L'option -t permet de spécifier la forme du plateau de jeu (grille carrée c, donut d, hachée h ou torique t ) (ex. -t h).
 * L'option -c permet de spécifier le nombre de couleurs utilisé dans la partie. Ce nombre est un entier compris entre 2 et MAX_COLOR (ex. -c 4 pour une partie à 4 couleurs).
 * L'option -a permet de spécifier l'algorithme de coloration utilisé. Il est demandé à ce que les algorithmes de coloration. Il existe trois algorithme de coloration : ALEATOIRE CYCLIQUE PONT. (ex. -a a pour l'algorithme de coloration aléatoire).
 * L'option -f permet de spécifier le nombre de couleurs interdites pour chaque joueur. (ex. -f 1 pour 1 couleur interdite).
 * Les clients sont passés en paramètre dans un ordre quelconque par défaut. 

