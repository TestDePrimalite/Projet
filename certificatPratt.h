#ifndef CERTIFICATPRATT_H
#define CERTIFICATPRATT_H

#include <stdio.h>
#include <stdlib.h>
#include "gmp.h"
#include <math.h>

#define MAXBUF 512

/*
Cette structure de donnée possède un pointeur vers une variable facteurs de type mpz_t, ainsi qu'un entier longueur.
La variable facteurs servira à stocker un tableau de taille longueur.
*/
struct facteursPremiers
{
	mpz_t *facteurs;
	int longueur;
} typedef facteursPremiers;

/*
Cette fonction utilise un algorithme naif de factorisation d'un nombre f de type mpz_t donné en entrée.
Elle va construire une variable de type facteursPremiers en préparant le tableau en allouant de la mémoire
dynamiquement. Au final, cette variable contiendra les facteurs premiers, mais on ne stocke pas leurs puissances
respectives (Car nous n'en avons pas l'utilité dans le programme).
*/
facteursPremiers factorisation(mpz_t f);

/*
Cette fonction va simplement libérer la mémoire de chaque case du tableau contenu dans f.
*/
void clearFacteursPremiers(facteursPremiers f);

/*
Cette fonction est la fonction principale de ce fichier. Elle prend un entier p de type mpz_t, ainsi qu'une variable
state de type gmp_randstate_t. La variable state sert uniquement à initialisé des nombre aléatoire avec la même graine.
La fonction à pour but de certifier si le nombre p est premier (Dans ce cas elle renvoie 1, et sinon elle renvoie 0), 
en utilisant le certificat de Pratt.
*/
int certificatPratt(mpz_t p, gmp_randstate_t state);

#endif
