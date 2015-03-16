#include <stdio.h>
#include <stdlib.h>
#include "gmp.h"
#include "lucasLehmerMersenne.h"
#include "lucasLehmerRiesel.h"
#include "certificatPratt.h"

int main(int argc, char const *argv[])
{
	int choix;
	int p, k, n_;
	mpz_t n;
	gmp_randstate_t state;
	gmp_randinit_default(state);
	mpz_init(n);

	do
	{
		printf("Test de primalité : \n");
		printf("1. Test de primalité de Lucas-Lehmer pour les nombres de Mersenne\n");
		printf("2. Test de primalité de Lucas-Lehmer-Riesel pour les nombres de Proth\n");
		printf("3. Certificats de primalité de Pratt\n");
		printf("4. Amélioration de Pocklington\n");
		printf("Autres nombres: Quitter\n");
		printf("Quel est votre choix? \n");
		scanf("%d", &choix);
		if(choix == 1)
		{
			printf("Veuillez donner une valeur à p. (Le test sera effectué sur le nombre de Mersenne 2^p - 1)\n\tp = ");
			scanf("%d", &p);
			if(lucasLehmerMersenne(p))
				printf("Ce nombre est premier.\n");
			else
				printf("Ce nombre n'est pas premier.\n");
		}
		else if(choix == 2)
		{
			printf("Test de la primalité de N = k * 2^n - 1.\nChoix de k ?\n");
			scanf("%d", &k);
			printf("Choix de n ?\n");
			scanf("%d", &n_);
			if (lucasLehmerRiesel((double)k, (double)n_))
				printf("Ce nombre est premier.\n");
			else
				printf("Ce nombre n'est pas premier.\n");
		}
		else if(choix == 3)
		{

			printf("Certificat de Pratt : Veuillez rentrer un nombre :\n");
			scanf("%d", &p);
			gmp_randseed_ui(state, p);
			if(certificatPratt(p, state))
				printf("Ce nombre est premier.\n");
			else
				printf("Ce nombre n'est pas premier.\n");
		}
		else if(choix == 4)
		{

		}
	}while(choix == 1 || choix == 2 || choix == 3 || choix == 4);
	

	return 0;
}
