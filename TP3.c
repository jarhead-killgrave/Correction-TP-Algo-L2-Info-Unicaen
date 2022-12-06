/* Vous pouvez mettre la fenêtre en plein écran (deux flèches)
Si vous voulez exécuter votre programme, sauvegardez (disquette) puis exécutez (fusée)
Vous pouvez même vérifier si votre programme est juste ! Sauvegarder puis évaluez (Case avec un "tick")
*/



#include <stdio.h>
#include <stdlib.h>


/***************** Définition et fonctions de base ****************************/

/*  Définition de la structure de noeud  */
struct noeud{
  int valeur;
  struct noeud * gauche;
  struct noeud * droit;
};

/*  Définition du type arbre qui est un pointeur sur noeud  */
typedef struct noeud * arbre;


/*  On alloue un noeud  */
struct noeud* Noeud(int x,arbre g,arbre d){
	struct noeud* n;
	n = malloc(sizeof(struct noeud));
	n -> valeur = x;
	n -> gauche = g;
	n -> droit = d;
	return n;
}

// Vous pourrez utiliser les deux fonctions suivantes    
int hauteur(arbre A){
    // fonction qui calcule la hauteur d'un arbre binaire A
    if (A == NULL){ 
		return -1;
	}
	int hg = hauteur(A -> gauche);
	int hd = hauteur(A -> droit); 
	if (hg < hd){
		return 1 + hd;
	}
	else {
		return 1 + hg;
	}
 }

void affiche_arbre(arbre A){
   // un affichage planaire de l'arbre


   
   void affichageProfondeur(arbre A,int profondeur){
      if (A == NULL){
         printf(" ");}
      else{
		  affichageProfondeur(A -> gauche,profondeur-1);
		  if (profondeur == 0)
			 printf("%d",A -> valeur);
		  else
			 printf(" ");
		  affichageProfondeur(A -> droit,profondeur-1);
	  }
	}
      
  if (A != NULL){
	int h = hauteur(A);
	for( int p = 0 ; p < h + 1 ; p++){
      affichageProfondeur(A,p); 
      printf("\n");
  }
}

}









/*
Exercice 1. Parcours en profondeur sur un arbre binaire
1.a Ecrivez une fonction qui affiche les valeurs des noeuds d'un arbre  binaire dans l'ordre préfixe.
1.b Ecrivez une fonction qui affiche les valeurs des noeuds d'un arbre  binaire dans l'ordre infixe.
1.c Ecrivez une fonction qui affiche les valeurs des noeuds d'un arbre  binaire dans l'ordre suffixe.
*/

void affiche_prefixe(arbre A){
	if (A != NULL){
		printf("%d ",A -> valeur);
		affiche_prefixe(A -> gauche);
		affiche_prefixe(A -> droit);
	}
}

void affiche_infixe(arbre A){
	if (A != NULL){
		affiche_infixe(A -> gauche);
		printf("%d ",A -> valeur);
		affiche_infixe(A -> droit);
	}
}

void affiche_suffixe(arbre A){
	if (A != NULL){
		affiche_suffixe(A -> gauche);
		affiche_suffixe(A -> droit);
		printf("%d ",A -> valeur);
	}
}

/*
Exercice 2. Ecrivez une fonction qui retourne le nombre de noeuds internes d'un arbre  binaire.
*/

size_t nombre_noeuds_internes(arbre A){
	if (A == NULL){
		return 0;
	}
	else if (A -> gauche == NULL && A -> droit == NULL){
		return 0;
	}
	else {
		return 1 + nombre_noeuds_internes(A -> gauche) + nombre_noeuds_internes(A -> droit);
	}
}

/*Exercice 3. Ecrivez une fonction est_degenere qui détermine si un arbre binaire est dégénéré
On rappelle qu'un arbre est dégénéré lorsque tout noeud a au plus un fils.
On renverra 1 s'il est dégénéré, 0 sinon.
*/

int est_degenere(arbre A){
	if (A == NULL){
		return 1;
	}
	else if (A -> gauche == NULL && A -> droit == NULL){
		return 1;
	}
	else if (A -> gauche == NULL && A -> droit != NULL){
		return est_degenere(A -> droit);
	}
	else if (A -> gauche != NULL && A -> droit == NULL){
		return est_degenere(A -> gauche);
	}
	else {
		return 0;
	}
}



/*Exercice 4. Ecrivez une fonction affiche_niveau(A,k) qui affiche les noeuds du niveau k
Indication : pendant les appels récursifs k diminue et correspond à la longueur de chemin à parcourir
pour atteindre un noeud de profondeur k, nous avons trois cas :
cas 1) A = None et on ne fait rien
cas 2) k = 0 le noeud est de profondeur k et on l'affiche
cas 3) k > 0 des noeuds de profondeur k peuvent se trouver dans les sous-arbres gauche et droit
on effectue deux appels récursifs sur les deux sous-arbres
*/
void affiche_niveau(arbre A, int k){
	if (A != NULL){
		if (k == 0){
			printf("%d ",A -> valeur);
		}
		else {
			affiche_niveau(A -> gauche,k-1);
			affiche_niveau(A -> droit,k-1);
		}
	}
}

/*Exercice 5. Ecrivez une fonction affiche_largeur qui affiche les valeurs des noeuds d'un arbre binaire
en suivant le parcours en largeur.
Vous pouvez utiliser les fonctions hauteur et afficheNiveau.*/

void affiche_largeur(arbre A){
	int h = hauteur(A);
	for (int i = 0 ; i < h + 1 ; i++){
		affiche_niveau(A,i);
	}
}

/*Exercice 6. On rappelle que la longeur de cheminement d'un arbre binaire est
la somme des profondeurs de tous les noeuds de cet arbre.
Ecrivez une fonction longueurCheminement qui calcule la longueur de cheminement
d'un arbre binaire A. */

size_t longueur_cheminement(arbre A){
	if (A == NULL){
		return 0;
	}
	else {
		return hauteur(A) + longueur_cheminement(A -> gauche) + longueur_cheminement(A -> droit);
	}
}


/*
Exercice 7. Un chemin décroissant dans un arbre est un chemin partant de la racine
dans lequel la valeur des noeuds décroît au fur et à mesure qu'on descend dans l'arbre.
Un chemin décroissant ne s'arrête pas forcément à une feuille.
Par exemple, dans monArbre1, il y a deux chemins décroissants :
 4-3-2 et 4-1.
 7.a)  Ecrivez une fonction qui renvoie la longueur du PLUS LONG chemin décroissant dans un arbre A
 7.b) (*) Ecrivez une fonction qui affiche le plus long chemin chemin décroissant dans un arbre A
*/


size_t longueur_plus_long_chemin_decroissant(arbre A){
	int gauche = 0;
	int droit = 0;
	// On retournera le maximum entre la longueur du plus long chemin décroissant dans le sous-arbre gauche et dans le sous-arbre droit

	// Si l'arbre est vide, on retourne 0
	if (A == NULL){
		return 0;
	}

	// On regarde à gauche puis à droite
	if(A -> gauche != NULL){
		if (A -> valeur > A -> gauche -> valeur){
			gauche = 1 + longueur_plus_long_chemin_decroissant(A -> gauche);
		}
	}
	if(A -> droit != NULL){
		if (A -> valeur > A -> droit -> valeur){
			droit = 1 + longueur_plus_long_chemin_decroissant(A -> droit);
		}
	}
	return max(gauche,droit);
}



void affiche_plus_long_chemin_decroissant(arbre a){
		if (a != NULL)
		{
			printf("%d", a->valeur);
		}
		if (a->gauche != NULL && a->gauche->valeur < a->valeur)
		{
			affiche_plus_long_chemin_decroissant(a->gauche);
		}
		if (a->droit != NULL && a->droit->valeur < a->valeur)
		{
			affiche_plus_long_chemin_decroissant(a->droit);
		}

}

/*Exercice 8. Étant donné un arbre binaire, le diamètre est la longueur du plus 
long chemin entre deux noeuds d'un arbre. 
Ce chemin peut passer et ne pas passer par la racine de l'arbre.
La longueur d'un chemin entre deux noeuds est égale au nombre d'arêtes qui les
séparent.
*/

size_t diametre(arbre a){
		int racine = 0, lgG = 0, lgD = 0;
		if (a != NULL)
		{

			racine = hauteur(a->gauche) + hauteur(a->droit) + 2;

			if (a->gauche != NULL)
			{
			lgG = diametre(a->gauche);
			}
			if (a->droit != NULL)
			{
			lgD = diametre(a->droit);
			}
			return max(max(racine, lgG), lgD);
		}
		return 0;
}


/***************** Pour tester vos fonctions : *********/
/* (ne pas touchez aux "ifndef" et "endif") */
#ifndef EVAL 

int main() {
	
	
	
	arbre monArbre1 = Noeud(4,Noeud(1,Noeud(3,Noeud(6,NULL,NULL),NULL),Noeud(9,NULL,NULL)),Noeud(3,Noeud(2,Noeud(5,NULL,NULL),NULL),Noeud(7,NULL,NULL)));
	arbre monArbre2 = Noeud(5,NULL,Noeud(3,Noeud(1,Noeud(9,NULL,NULL),NULL),NULL) );
	
	printf("monArbre1 :\n");
	affiche_arbre(monArbre1);

	printf("monArbre2 :\n");
	affiche_arbre(monArbre2);

    return EXIT_SUCCESS;	
}
#endif
