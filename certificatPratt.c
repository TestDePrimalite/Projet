#include "certificatPratt.h"

facteursPremiers factorisation(mpz_t f)
{
	mpz_t i;
	facteursPremiers fact;
	mpz_t tab[1024];
	int marqueur = 0, j;
	mpz_t racine;
	mpz_t resultatMod;
	mpz_t fCopie;

	mpz_init(resultatMod);
	mpz_init(racine);
	mpz_init_set_ui(i, 2);
	mpz_sqrt(racine, f);
	mpz_init_set(fCopie, f);
	gmp_printf("On factorise le nombre %Zd\n", f);
	fact.longueur = 0;
	while(mpz_cmp(racine,i) >= 0)		// Valeur positive ou nulle si racine >= i 
	{
		gmp_printf("f = %Zd et i = %Zd et racine = %Zd\n", fCopie, i, racine);
		mpz_mod(resultatMod, fCopie, i);
		if(mpz_cmp_ui(resultatMod, 0) == 0)		// Si f % i = 0 (Equivaut a resultatMod = 0)
		{
			while(mpz_cmp_ui(resultatMod, 0) == 0)
			{
				mpz_divexact(fCopie, fCopie, i);
				mpz_mod(resultatMod, fCopie, i);
				gmp_printf("fCopie = %Zd\n", fCopie);
			}
			fact.longueur ++;
			mpz_init_set(tab[marqueur], i);
			marqueur++;
		}
		mpz_add_ui(i, i, 1);		// Equivaut à i = i + 1
	}
	if(fact.longueur == 0)
	{
		fact.longueur = 1;
		mpz_init_set(tab[marqueur], i);
	}
	else if(mpz_cmp_ui(fCopie, 1) > 0)
	{
		fact.longueur++;
		mpz_init_set(tab[marqueur], fCopie);		// Il faut rajouter le dernier facteur
	}
	fact.facteurs = malloc(fact.longueur * sizeof(mpz_t));
	printf("Nombre de facteurs : %d\n", fact.longueur);
	for(j = 0; j < fact.longueur; j++)
	{
		mpz_init_set(fact.facteurs[j], tab[j]);		// Equivaut à fact.facteurs[i] = tab[i]
		gmp_printf("Facteur %d = %Zd\n",j , fact.facteurs[j]);
	}
	gmp_printf("fCopie = %Zd\n", fCopie);

	return fact;
}

static void clearAll(mpz_t a, mpz_t p_1, mpz_t resultatPgcd, mpz_t resultatMod, mpz_t resultatCalcul, mpz_t puis)
{
	mpz_clear(a);
	mpz_clear(p_1);
	mpz_clear(resultatPgcd);
	mpz_clear(resultatMod);
	mpz_clear(resultatCalcul);
	mpz_clear(puis);
}

int certificatPratt(mpz_t p, gmp_randstate_t state)
{
	FILE *fichier = NULL;
	mpz_t a;
	mpz_t p_1;
	mpz_t resultatPgcd;
	mpz_t resultatMod;
	mpz_t resultatCalcul;
	mpz_t puis;

	
	int i;

	
	
	mpz_init(a);
	
	
	mpz_init_set(p_1, p);
	mpz_sub_ui(p_1, p_1, 1);
	mpz_init(resultatPgcd);
	mpz_init(resultatMod);
	mpz_init(resultatCalcul);
	mpz_init(puis);
	fichier = fopen("nombresPremiers.txt", "r+");
	if(fichier == NULL)
	{
		printf("Erreur lors de l'ouverture du fichier nombresPremiers.txt.\n");

		exit(1);
	}
	if(mpz_cmp_ui(p, 2) == 0)
	{
		clearAll(a, p_1, resultatPgcd, resultatMod, resultatCalcul, puis);
		fclose(fichier);

		return 1;
	}
	else
	{
		do
		{
			mpz_urandomm(a, state, p); gmp_printf("Ici notre a vaut a = %Zd et p = %Zd\n", a, p);
		}while(mpz_cmp_ui(a, 0) == 0 || mpz_cmp_ui(a, 1) == 0);
		//gmp_printf("p = %d ! et a = %Zd , n = %Zd, n_1 = %Zd\n",p, a, n, n_1);
		mpz_gcd(resultatPgcd, a, p);
		// gmp_printf("resultatPgcd = %Zd\n", resultatPgcd);
		mpz_powm(resultatMod, a, p_1, p);
		//gmp_printf("resultatMod = %Zd\n", resultatMod);
		if(mpz_cmp_ui(resultatPgcd, 1) == 0 && mpz_cmp_ui(resultatMod, 1) == 0)	// Si pgcd(a,b) = 1 et a^(n-1) = 1 mod n
		{
			facteursPremiers fact = factorisation(p_1);
			i = 0;
			while(i < fact.longueur)
			{
				// printf("ici i = %d et fact.longueur = %d et facteurs = %d\n", i, fact.longueur, fact.facteurs[i]);
				if(certificatPratt(fact.facteurs[i], state) == 1)
				{
					mpz_cdiv_q(puis, p_1, fact.facteurs[i]);
					gmp_printf("puis = %Zd\n", puis);
					mpz_powm(resultatCalcul, a, puis, p);
					if(mpz_cmp_ui(resultatCalcul, 1) == 0)		// Si resultatCalcul = 1
					{
						gmp_printf("resultatCalcul = %Zd\n", resultatCalcul);
						clearAll(a, p_1, resultatPgcd, resultatMod, resultatCalcul, puis);
						fclose(fichier);

						return certificatPratt(p, state);		// On relance un certificat pour choisir un a aléatoire différent
					}
				}
				else
				{
					printf("Erreur : Un nombre dans la factorisation n'est pas premier.\n");
					clearAll(a, p_1, resultatPgcd, resultatMod, resultatCalcul, puis);
					fclose(fichier);
					exit(1);
				}
				i = i + 1;
			}
			clearAll(a, p_1, resultatPgcd, resultatMod, resultatCalcul, puis);
			fclose(fichier);

			return 1;
		}
		else
		{
			clearAll(a, p_1, resultatPgcd, resultatMod, resultatCalcul, puis);
			fclose(fichier);

			return 0;
		}	
	}
	clearAll(a, p_1, resultatPgcd, resultatMod, resultatCalcul, puis);
	fclose(fichier);

	return 1;
}
