/* Vous pouvez mettre la fenêtre en plein écran (deux flèches)
Si vous voulez exécuter votre programme, sauvegardez (disquette) puis exécutez (fusée)
Vous pouvez même vérifier si votre programme est juste ! Sauvegarder puis évaluez (un nombre à côté d'une' case avec un "tick")
*/


#include <stdio.h>
#include <stdlib.h>



/*  Définition de la structure de noeud  */
struct noeud{
  int valeur;
  struct noeud * gauche;
  struct noeud * droit;
};

/*  Définition du type ABR qui est un pointeur sur noeud  */
typedef struct noeud * ABR;


/*  On alloue un noeud  */
struct noeud* Noeud(int x, ABR g, ABR d){
	struct noeud* n;
	n = malloc(sizeof(struct noeud));
	n -> valeur = x;
	n -> gauche = g;
	n -> droit = d;
	return n;
}



/* Cette fonction calcule la hauteur d'un ABR */
int hauteur(ABR A){
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


/* Pour afficher un ABR */
void affiche(ABR A){
 
   void affichageProfondeur(ABR A,int profondeur){
      if (A == NULL){
         printf(" ");}
      else{
		  affichageProfondeur(A -> gauche,profondeur-1);
		  if (profondeur == 0)
			 printf("%2d",A -> valeur);
		  else
			 printf("  ");
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



/*************** Début des exercices *********************/

/* Question 1. Écrivez une fonction minimum qui prend en paramètre 
 * un ABR A et qui retourne un pointeur sur le noeud de valeur minimale 
 * de A. La fonction renvoie un pointeur nul si l'arbre est vide. */
 
ABR minimum(ABR A){
	if (A == NULL){
		return NULL;
	}
	else if (A -> gauche == NULL){
		return A;
	}
	else {
		return minimum(A -> gauche);
	}
}



/* 2. Écrivez une fonction itérative present qui prend en argument un
 *  ABR A et un entier x et qui détermine si l'élément x est présent ou 
 * non dans l'ABR A. La fonction retourne un pointeur sur le noeud
 *  contenant la valeur x si x est présent et sinon renvoie un pointeur
 * nul */
 
ABR present(ABR A, int x){
	while (A != NULL){
		if (A -> valeur == x){
			return A;
		}
		else if (A -> valeur > x){
			A = A -> gauche;
		}
		else {
			A = A -> droit;
		}
	}
	return NULL;
}

 
/* 3a. Écrivez une fonction récursive insereFeuille(A,x) qui 
 * renvoie l'ABR A enrichi de l'élément x inséré au niveau des feuilles.
 * Lorsque x est déjà dans l'arbre, la fonction ne modifie pas l'ABR. */
 
ABR insereFeuille(ABR A, int x){
	if (A == NULL){
		return Noeud(x,NULL,NULL);
	}
	else if (A -> valeur == x){
		return A;
	}
	else if (A -> valeur > x){
		A -> gauche = insereFeuille(A -> gauche,x);
		return A;
	}
	else {
		A -> droit = insereFeuille(A -> droit,x);
		return A;
	}
}
 
/* 3b. Écrivez la même fonction de manière itérative. */

ABR insereFeuilleIteratif(ABR A, int x){
	ABR n = Noeud(x,NULL,NULL);
	if (A == NULL){
		return n;
	}
	ABR p = A;
	while (p -> valeur != x){
		if (p -> valeur > x){
			if (p -> gauche == NULL){
				p -> gauche = n;
				return A;
			}
			else {
				p = p -> gauche;
			}
		}
		else {
			if (p -> droit == NULL){
				p -> droit = n;
				return A;
			}
			else {
				p = p -> droit;
			}
		}
	}
	return A;
}

/* 4. Écrire une fonction afficheCroissant qui prend en paramètre un ABR
 * A et qui affiche les valeurs des noeuds de A dans l'ordre 
 * croissant. */
 
void afficheCroissant(ABR A){
	if (A != NULL){
		afficheCroissant(A -> gauche);
		printf("%d ",A -> valeur);
		afficheCroissant(A -> droit);
	}
}

/* 5.  Écrivez une fonction récursive afficheIntervalle(A, debut, fin)
 * qui affiche toutes les valeurs x de A telles que deb <= x <= fin.
 * Évitez les parcours de sous-arbres inutiles. */
 
void afficheIntervalle(ABR A, int debut, int fin){
	if (A != NULL){
		if (A -> valeur >= debut){
			afficheIntervalle(A -> gauche,debut,fin);
		}
		if (A -> valeur >= debut && A -> valeur <= fin){
			printf("%d ",A -> valeur);
		}
		if (A -> valeur <= fin){
			afficheIntervalle(A -> droit,debut,fin);
		}
	}
}

/* 6. On souhaite définir une fonction rechercheKieme
 * qui retourne la kième plus petite valeur d'un ABR A, pour un entier 
 * k >= 1.
 * 
 * Le principe est d'effectuer un parcours infixé.
 * On part de j = k et on décrémente ensuite i lors de la visite de
 * chaque noeud.
 * Lorsque l'on arrive à j = 1, la valeur du noeud courant est la kième 
 * plus petite valeur de A.
 * 
 * On utilisera une fonction auxiliaire rechercheKiemeAux(B),
 * où B est un sous-arbre de A 
 *
 * La fonction rechercheKiemeAux utilise un entier j déclaré dans la 
 * fonction rechercheKieme mais hors rechercheKiemeAux.
 * Si j = 0 alors on a trouvé la kième plus petite valeur de A.
 * Sinon j est le nombre de noeuds qu'il reste à parcourir et la valeur
 * qu'on renvoie n'importe.
 * On effectue un appel récursif sur le sous-arbre gauche 
 * si j = 0 alors la valeur envoyée par les enfants est la valeur recherchée
 * si j = 1 alors nous sommes sur le kième noeud
 * si j > 1 alors on continue sur le sous-arbre droit. */




int rechercheKieme(ABR A, int k){
	
	int j=k;	
	
	int rechercheKiemeAux(ABR B){
		
		if (B == NULL){
			return -1;
		}
		int res = rechercheKiemeAux(B->gauche);
		
		if ( j==0 ){
			; // A compléter
		}
		else if (j == 1) {
			; // A compléter
		}
		else{
			j--;
			res = rechercheKiemeAux(B->droit);
		}
		return res;
	}
	return rechercheKiemeAux(A);
}




/* 7. Écrivez une fonction coupeSelon qui, pour un ABR A et un élément x
 *   (présent ou non dans A),retourne une coupe (cf type défini plus bas).
 *   L'argument inf pointe vers un ABR dont les éléments sont ceux de A
 *   qui sont strictement inférieurs à x ;
 *   l'argument sup pointe vers un ABR dont les éléments sont ceux de A
 *   qui sont strictement supérieurs à x.     */


typedef struct noeudCoupe{
    ABR inf;
    ABR sup;
} coupe;

coupe coupeSelon(ABR A, int x){
	coupe c;
	if (A == NULL){
		c.inf = NULL;
		c.sup = NULL;
		return c;
	}
	if (A -> valeur == x){
		c.inf = A -> gauche;
		c.sup = A -> droit;
		return c;
	}
	if (A -> valeur > x){
		c = coupeSelon(A -> gauche,x);
		A -> gauche = c.sup;
		c.sup = A;
		return c;
	}
	else {
		c = coupeSelon(A -> droit,x);
		A -> droit = c.inf;
		c.inf = A;
		return c;
	}
}

/* 8.  Écrivez une fonction insereAlaRacine qui retourne l'ABR A
 *     où on ajoute l'élément x comme racine.
 *     Vous utiliserez pour cela la procédure coupeSelon. 
 *     N'oubliez pas de libérer la mémoire associée à la coupe ! (free) */
 

ABR insereAlaRacine(ABR A, int x){
	coupe c = coupeSelon(A,x);
	ABR B = Noeud(x,c.inf,c.sup);
	free(c.inf);
	free(c.sup);
	return B;
}

/* 9.  Écrivez une fonction *récursive* fusion qui retourne la 
 *     fusion de deux ABR A et B.
 *     On utilisera la fonction coupeSelon appliquée à B et à A -> valeur 
 *     N'oubliez pas de libérer la mémoire associée à la coupe ! (free) */
 
ABR fusion (ABR A, ABR B){
	if (A == NULL){
		return B;
	}
	if (B == NULL){
		return A;
	}
	coupe c = coupeSelon(B,A -> valeur);
	A -> gauche = fusion(A -> gauche,c.inf);
	A -> droit = fusion(A -> droit,c.sup);
	free(c.inf);
	free(c.sup);
	return A;
}



/***************** Pour tester vos fonctions : *********/
/* (ne pas touchez aux "ifndef" et "endif") */
#ifndef EVAL 

int main(){
    
    ABR A = Noeud(21,Noeud(10,Noeud(5,Noeud(2,NULL,NULL),Noeud(7,NULL,NULL)),NULL),Noeud(36,Noeud(26,Noeud(22,NULL,NULL),Noeud(29,NULL,NULL)),Noeud(45,NULL,NULL)));
    affiche(A);
  
}

#endif