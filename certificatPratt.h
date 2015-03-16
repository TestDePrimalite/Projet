#ifndef CERTIFICATPRATT_H
#define CERTIFICATPRATT_H

#include <stdio.h>
#include <stdlib.h>
#include "gmp.h"
#include <math.h>

struct facteursPremiers
{
	int *facteurs;
	int longueur;
} typedef facteursPremiers;
int certificatPratt(int p, gmp_randstate_t state);

#endif