/* Vous pouvez mettre la fenêtre en plein écran (deux flèches)
Si vous voulez exécuter votre programme, sauvegardez (disquette) puis exécutez (fusée)
Vous pouvez même vérifier si votre programme est juste ! Sauvegarder puis évaluez (Case avec un "tick")
*/


#include <stdio.h>
#include <stdlib.h>



/***************** Définition de la structure **************************/

/*  Définition de la structure de noeud  */
struct noeud{
  int valeur;
  struct noeud * suivant;
};

/*  Définition du type liste qui est un pointeur sur noeud  */
typedef struct noeud * liste;


/***************** Fonctions utiles **************************/

/*  Fonction affichant les valeurs des noeuds d'une liste L  */
void afficheListe(liste L){
    if (L == NULL) printf("[X]\n");
    while(L != NULL){
        printf("[%d,",L->valeur);
        L = L->suivant;
        if (L == NULL){
            printf("X]\n");
        }
        else{
            printf("-]-->");
        }
    }
}

/*  nouveauNoeud(x) crée une nouvelle liste contenant un noeud 
 * avec la valeur x et le suivant égal à NULL  */
liste nouveauNoeud(int x){
	liste L = malloc(sizeof(struct noeud));
	L->valeur = x;
	L->suivant = NULL;
	return L;
}


/*  Fonction insérant un nouveau noeud de valeur x au début de la liste L  */
liste insereDebut(liste L, int x){
    liste tmp = nouveauNoeud(x);
    if (L != NULL) {
        tmp->suivant = L;
    }
    return tmp;
}

/******************** Début des questions ********************/


/*  Question 1. Écrivez une fonction qui étant donnée un entier positif
 *  "taille" renvoie une liste chaînée de taille "taille" dont la valeur
 *	de chaque élément est 0. 
 *  On pourra utiliser la fonction "insereDebut" donnée plus haut. */
 
liste listeZeros(size_t taille){
    liste L = NULL;
    for (size_t i = 0; i < taille; i++){
        L = insereDebut(L,0);
    }
    return L;
}


/* Question 2. Écrire une fonction qui calcule le nombre de noeuds 
 * d'une liste chaînée L */
 
size_t nombreNoeuds(liste L){
    size_t n = 0;
    while(L != NULL){
        n++;
        L = L->suivant;
    }
    return n;
}



/* Question 3. On veut écrire une fonction qui insère un nouveau noeud 
 * de valeur x à la fin d'une liste L.
 * On renverra la liste ainsi obtenue.  */
 
 
/* Question 3a. Écrire une fonction itérative de cette fonction. */

liste insererFinIt(liste L, int x){
    liste tmp = L;
    if (L == NULL){
        return nouveauNoeud(x);
    }
    while(tmp->suivant != NULL){
        tmp = tmp->suivant;
    }
    tmp->suivant = nouveauNoeud(x);
    return L;
}

/* Question 3b. Écrire une fonction récursive de cette fonction. */

liste insererFinRec(liste L, int x){
    if (L == NULL){
        return nouveauNoeud(x);
    }
    L->suivant = insererFinRec(L->suivant,x);
    return L;
}



/* Question 4. Écrire une fonction retournant l'adresse (le pointeur 
 * sur le noeud, autrement dit une "liste") du premier noeud contenant 
 * la valeur x.
 * On retournera NULL lorsque la liste ne contient pas la valeur x.  */
 
liste recherche(liste L, int x){
    while(L != NULL){
        if (L->valeur == x){
            return L;
        }
        L = L->suivant;
    }
    return NULL;
}


/* La fonction précédente permet de faire fonctionner la fonction suivante :
 * Elle insère un nouveau noeud avec la valeur y après le premier noeud 
 * contenant la valeur x. S'il n'y a pas de noeud contenant la valeur x,
 * cette fonction ne fait rien.  */ 
 
//A decommenter 
 

liste  insereApres(liste L, int x, int y){
    liste tmp = recherche(L,x);
    if (tmp != NULL){
        liste tmp2 = tmp->suivant;
        tmp->suivant = nouveauNoeud(y);
        tmp->suivant->suivant = tmp2;
    }
    return L;
}


/* Question 5. S'inspirer de la fonction précédente pour écrire une 
 * fonction insérant un nouveau noeud avec la valeur y *avant* le
 * premier noeud contenant la valeur x.
 * S'il n'y a pas de noeud contenant la valeur x, cette fonction ne fait
 * rien.  
 * Astuce : on reprend la fonction insereApres et on échange les 
 * valeurs x et y  */
 
liste insereAvant(liste L, int x, int y){
    liste tmp = recherche(L,y);
    if (tmp != NULL){
        liste tmp2 = tmp->suivant;
        tmp->suivant = nouveauNoeud(x);
        tmp->suivant->suivant = tmp2;
    }
    return L;
}




/* Question 6. Écrire une fonction retourne qui prend en paramètre
 * une liste L et qui *modifie* L de sorte que ses élements
 * apparaissant dans l'ordre inversé.
 * On renverra la liste ainsi modifiée (pointant sur le dernier noeud 
 * de L).
 * Vous ne devez pas changer la valeur des noeuds, seulement réordonner
 * les pointeurs.
 * Exemple : Si L est la liste chaînée ->[1,-]-->[2,-]-->[3,X] alors on doit
 * renvoyer la liste [1,X]  [2,|]   [3,|]<-- 
 *                      ↖______| ↖_____|     */
 
liste retourne(liste L){
    liste tmp = NULL;
    while(L != NULL){
        liste tmp2 = L->suivant;
        L->suivant = tmp;
        tmp = L;
        L = tmp2;
    }
    return tmp;
}


/* Question 7. Écrire une fonction qui prend en paramètre une liste chaînée
 * L et qui renvoie une *nouvelle* liste chaînée de même longueur que L
 * dans laquelle l'élément en position i prend pour valeur
 * la valeur maximale que prend un noeud de L situé en position i ou 
 * après la position i.
 * Par exemple, si on exécute la fonction sur la liste L
 * ->[7,-]-->[20,-]-->[11,-]-->[6,-]-->[15,-]-->[12,-]-->[10,X]
 * on doit renvoyer
 * ->[20,-]-->[20,-]-->[15,-]-->[15,-]-->[15,-]-->[12,-]-->[10,X]
 * En effet, la valeur maximale de la liste L est 20, donc le premier
 * élément de la nouvelle liste a pour valeur 20 ;
 * la valeur maximale de la liste L à partir de la deuxième position est
 * toujours 20, donc le deuxième élément de la nouvelle liste a aussi
 * valeur 20 ;
 * par contre, la valeur maximale de la liste L à partir de la troisième
 * position est 15 ; donc le troisième élément de la nouvelle liste aura
 * pour valeur 15 ;
 * etc.
 * */

liste listeMaximums(liste L){
    liste tmp = NULL;
    int max = 0;
    while(L != NULL){
        if (L->valeur > max){
            max = L->valeur;
        }
        tmp = insererFinRec(tmp,max);
        L = L->suivant;
    }
    return tmp;
}




/***************** Pour tester vos fonctions : *********/
/* (ne pas touchez aux "ifndef" et "endif") */
#ifndef EVAL 

int main(){

    liste L1;
	L1 = nouveauNoeud(10);
	L1 -> suivant = nouveauNoeud(7);
	L1 -> suivant -> suivant = nouveauNoeud(18);
	printf("Voici L1 : ");
	afficheListe(L1);
	
	return EXIT_SUCCESS;
}

#endif
