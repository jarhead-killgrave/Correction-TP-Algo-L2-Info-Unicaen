/* Vous pouvez mettre la fenêtre en plein écran (deux flèches)
Si vous voulez exécuter votre programme, sauvegardez (disquette) puis exécutez (fusée)
Vous pouvez même vérifier si votre programme est juste ! Sauvegarder puis évaluez (Case avec un "tick")
*/


#include <stdio.h>
#define TAILLEMAX 100*1000
#include <math.h>
#include <stdlib.h>
#include <time.h>



/************ MANIPULATION BASE TABLEAU ****************/

/* Question 1. Écrivez une fonction qui affiche les éléments d'un tableau*/
void affiche_tableau(int *tab, size_t taille){
  for (int i=0; i<taille; i++){
	printf("%d ",tab[i]);
  }
  printf("\n");
}


/* Question 2. Écrivez une fonction qui remplit un tableau en demandant des valeurs à l'utilisateur*/
void remplissage(int *tab, size_t taille){
  for (int i=0; i<taille; i++){
	printf("Entrez un entier : ");
	scanf("%d",&tab[i]);
  }
}


/* Question 3. Écrivez une fonction qui remplit un tableau par les valeurs 1,2,3,4,5,... dans cet ordre */
void numerotage(int *tab, size_t taille){
  for (int i=0; i<taille; i++){
	tab[i]=i+1;
  }
}


/************ RECHERCHE DANS UN TABLEAU ****************/

/* Question 4. Écrivez une fonction qui étant donné un tableau d'entier "tab"
 * de taille "taille" et un entier "x" 
 * renvoie la position de l'entier x dans le tableau, s'il existe 
 * (s'il y a plusieurs occurrences de 'x', n'importe quelle position convient)
 * renvoie -1 si x n'est pas dans le tableau.
 * Le tableau n'est pas forcément trié.
 */

int recherche(int *tab, size_t taille, int x){
  for (int i=0; i<taille; i++){
	if (tab[i]==x){
		return i;
	}
  }
  return -1;
}


/* Question 5. Écrivez une fonction qui étant donné un tableau d'entier "tab"
 * de taille "taille" et un entier "x" 
 * renvoie la position de l'entier x dans le tableau, s'il existe 
 * (s'il y a plusieurs occurrences de 'x', n'importe quelle position convient) ;
 * renvoie -1 si x n'est pas dans le tableau.
 * Le tableau est forcément TRIÉ ; on utilisera donc une recherche dichotomique.
 */

int dichotomie(int *tab, size_t taille, int x){
  int gauche=0;
  int droite=taille-1;
  int milieu;
  while (gauche<=droite){
	milieu=(gauche+droite)/2;
	if (tab[milieu]==x){
		return milieu;
	}
	else if (tab[milieu]<x){
		gauche=milieu+1;
	}
	else{
		droite=milieu-1;
	}
  }
  return -1;
}



/************ INSERTION DANS UN TABLEAU TRIE  ****************/


/* Question 6. Écrivez une fonction qui insère un élément dans un tableau trié 
 * de sorte qu'il reste trié (voir le CM 1) 
 * Par exemple, si tab = {14,21,24,25}, 
 * la fonction insertion(tab,4,17) modifie tab de sorte que
 * tab soit égal à {14,17,21,24,25}.
 * La taille du tableau sera gérée de manière externe.
 */
 
void insertion(int *tab, size_t taille, int x){
  int i=taille-1;
  while (i>=0 && tab[i]>x){
	tab[i+1]=tab[i];
	i--;
  }
  tab[i+1]=x;
}


/* Question 7. Écrivez une fonction qui trie sur place un tableau non trié.
 * Pour cela, la fonction insèrera de manière triée les différentes valeurs
 * du tableau dans l'ordre croissant.
*/

void tri_insertion(int *tab, size_t taille){
  for (int j=1; j<taille; j++){
	insertion(tab,j,tab[j]);
  }
}


/********** TEST RAPIDITE *************/


/* Question 8. Écrire une fonction qui renvoie le nombre de fois en moyenne que votre 
 * fonction "recherche" accède à un élément d'un tableau selon la taille du tableau.
 * Par "accéder à un élément", on entend lire un élément à une position donnée "tab[i]"
 * ou modifier un élément à une position donnée "tab[i]=..."
 * Par "en moyenne", on veut dire que pour chaque élément tab[j] d'un tableau tab, on regarde
 * combien de fois on accède à un élément quand on effectue recheche(tab,taille,tab[j])
 * puis on renvoie la moyenne des nombres obtenus.
 * Par exemple, pour un tableau de taille 2 {11,14},
 * si on recherche dans l'ordre gauche/droite,
 * on effectue 1 accession quand on recherche l'élément 11 (on teste d'abord tab[0] == 11, et on s'arrête là)
 * et on effectue 2 accessions quand on recherche l'élément 14 (on teste tab[0] == 14, puis tab[1] == 14)
 * Donc en moyenne, on fait 1.5 accessions.
*/
float complexite_moyenne_recherche(size_t taille){
	  int tab[taille];
  numerotage(tab,taille);
  int somme=0;
  for (int i=0; i<taille; i++){
	somme+=recherche(tab,taille,tab[i]);
  }
  return (float)somme/taille;
}


/* Question 9. Même question avec dichotomie */
float complexite_moyenne_dichotomie(size_t taille){
	  int tab[taille];
  numerotage(tab,taille);
  int somme=0;
  for (int i=0; i<taille; i++){
	somme+=dichotomie(tab,taille,tab[i]);
  }
  return (float)somme/taille;
}



/* Question 10. Même question avec tri_insertion.
 * Ici, par moyenne, on souhaire tester la fonction en remplissant un tableau par des valeurs aléatoires.
 * (Rappel : rand() renvoie un entier aléatoire)
 * On renverra juste le nombre d'accessions pour une seule entrée aléatoire.
 */
int complexite_moyenne_tri_insertion(size_t taille){
  int tab[taille];
  for (int i=0; i<taille; i++){
	tab[i]=rand();
  }
  tri_insertion(tab,taille);
  return recherche(tab,taille,tab[rand()%taille]);
}


/* Question 11 (non évaluée par caseine). Comparez les nombres que vous avez obtenus avec le 
 * temps que met chaque fonction à être exécutée sur des tableaux remplis par des nombres aléatoires.
 * On testera cela selon plusieurs tailles : 100,1000,1000000... 
 * Pour évaluer la rapidité d'une de vos fonctions, on pourra utiliser les lignes de codes suivantes.


    clock_t t;
	t = clock();
    fonction_tableau(tableau_aleatoire,taille_test);
    t = clock() - t; 
    printf("La fonction a mis %f secondes pour traiter une entrée aléatoire de taille %ld.\n", ( (double) t)/CLOCKS_PER_SEC , taille_test);


  */



/********** NOMBRE ELEMENTS DISTINCTS *************/



/* Question 11. Écrire une fonction qui renvoie le nombre d'éléments distincts
 * contenu dans un tableau de taille donnée.
 * Par exemple, si tab = {15,4,15,38,4,4,4},
 * alors nombre_elements_distincts(tab,7) doit renvoyer 4. */


size_t nombre_elements_distincts(int *tab, size_t taille){
  tri_insertion(tab,taille);
  int nb=1;
  for (int i=1; i<taille; i++){
	if (tab[i]!=tab[i-1]){
	  nb++;
	}
  }
  return nb;
}


/* Question 12. Défi ! Réussirez-vous à coder efficacement la fonction
* nombre_elements_distincts de sorte qu'il puisse traiter une entrée de taille 
* 100 000 en moins de 1 seconde ?*/
 
 
 
 

/***************** Pour tester vos fonctions : *********/
/* (ne pas touchez aux "ifndef" et "endif") */
#ifndef EVAL 

int main(){

	//A décommenter :
	//int tab1[TAILLEMAX] = {56,4,3,15,8};
	//affiche_tableau(tab1,5);
	
	//A décommenter :
	//int tab2[TAILLEMAX];
	//remplissage(tab2,3);
	//affiche_tableau(tab2,3);
	
	
	return 0;
}

#endif