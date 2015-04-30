#ifndef CERTIFICATPRATT_H
#define CERTIFICATPRATT_H

#include <stdio.h>
#include <stdlib.h>
#include "gmp.h"
#include <math.h>

struct facteursPremiers
{
	mpz_t *facteurs;
	int longueur;
} typedef facteursPremiers;

facteursPremiers factorisation(mpz_t f);
int certificatPratt(mpz_t p, gmp_randstate_t state);

#endif
