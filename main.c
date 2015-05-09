#include <stdio.h>
#include <stdlib.h>
#include "gmp.h"
#include "lucasLehmerMersenne.h"
#include "lucasLehmerRiesel.h"
#include "certificatPratt.h"
#include "pocklington.h"

int main(int argc, char const *argv[])
{
	int choix;
	int k, n;
	int valeurCertificat;
	facteursPremiers f;
	mpz_t p, p_1;
	gmp_randstate_t state;
	
	gmp_randinit_default(state);
	mpz_init(p);
	mpz_init(p_1);
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
			printf("Veuillez donner une valeur à k. (Le test sera effectué sur le nombre de Mersenne 2^k - 1)\n\tk = ");
			scanf("%d", &k);
			if(lucasLehmerMersenne(k))
				printf("Ce nombre est premier.\n");
			else
				printf("Ce nombre n'est pas premier.\n");
		}
		else if(choix == 2)
		{
			printf("Test de la primalité de N = k * 2^n - 1.\nChoix de k ?\n");
			scanf("%d", &k);
			printf("Choix de n ?\n");
			scanf("%d", &n);
			if (lucasLehmerRiesel((double)k, (double)n))
				printf("Ce nombre est premier.\n");
			else
				printf("Ce nombre n'est pas premier.\n");
		}
		else if(choix == 3)
		{

			printf("Certificat de Pratt : Veuillez rentrer un nombre :\n");
			gmp_scanf("%Zd", &p);
			gmp_randseed(state, p);
			valeurCertificat = certificatPratt(p, state);
			if(valeurCertificat == 1)
				gmp_printf("Le nombre %Zd est premier.\n", p);
			else if(valeurCertificat == -1)
				gmp_printf("Une erreur s'est produite: on ne peut rien conclure.\n");
			else
				gmp_printf("Le nombre %Zd n'est pas premier.\n", p);
		}
		else if(choix == 4)
		{
			printf("Test de Pocklington : Veuillez rentrer un nombre :\n");
			gmp_scanf("%Zd", &p);
			mpz_sub_ui(p_1, p, 1);
			f = factorisation(p_1);
			if(pocklington(p, &f))
				printf("Ce nombre est premier.\n");
			else
				printf("Ce nombre n'est pas premier.\n");
		}
	}while(choix == 1 || choix == 2 || choix == 3 || choix == 4);
	mpz_clear(p);

	return 0;
}
