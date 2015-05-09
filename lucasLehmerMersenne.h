#ifndef LUCASLEHMERMERSENNE_H
#define LUCASLEHMERMERSENNE_H

#include <stdio.h>
#include <stdlib.h>
#include "gmp.h"
#include <math.h>

/*
Cette fonction prend en entrée un entier p. Elle a pour objectif de vérifier si le nombre de Mersenne
m = 2^p - 1 est premier ou non: Si premier, on renvoie 1, sinon on renvoie 0. Le p doit être supérieur 
ou égal à 2. Si p n'est pas premier, la fonction renverra forcément 0.
*/
int lucasLehmerMersenne(int p);

#endif