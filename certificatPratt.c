#include "certificatPratt.h"

facteursPremiers factorisation(int f)
{
	int i;
	facteursPremiers fact;
	int tab[1024];
	int marqueur = 0;
	int racine = sqrt(f);

	printf("On factorise le nombre %d\n", f);
	fact.longueur = 0;
	for(i = 2; i <= racine; i ++)
	{printf("f = %d et i = %d et racine = %d\n", f, i, racine);
		if(f % i == 0)
		{
			while(f % i == 0)
				f = f / i;
			fact.longueur ++;
			tab[marqueur] = i;
			marqueur++;
		}
	}
	if(fact.longueur == 0)
	{
		fact.longueur = 1;
		tab[marqueur] = f;
	}
	fact.facteurs = malloc(fact.longueur * sizeof(int));
	printf("Nombre de facteurs : %d\n", fact.longueur);
	for(i = 0; i < fact.longueur; i++)
	{
		fact.facteurs[i] = tab[i];
		printf("Facteur %d = %d\n",i , fact.facteurs[i]);
	}

	return fact;
}

static void clearAll(mpz_t a, mpz_t n, mpz_t n_1, mpz_t resultatPgcd, mpz_t resultatMod, mpz_t resultatCalcul, mpz_t puis)
{
	mpz_clear(a);
	mpz_clear(n);
	mpz_clear(n_1);
	mpz_clear(resultatPgcd);
	mpz_clear(resultatMod);
	mpz_clear(resultatCalcul);
	mpz_clear(puis);
}

int certificatPratt(int p, gmp_randstate_t state)
{
	FILE *fichier = NULL;
	mpz_t a;
	mpz_t n;
	mpz_t n_1;
	mpz_t resultatPgcd;
	mpz_t resultatMod;
	mpz_t resultatCalcul;
	mpz_t puis;

	
	int i;

	
	mpz_init_set_ui(n, p);
	
	mpz_init(a);
	
	
	mpz_init_set_ui(n_1, p - 1);
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
	if(mpz_cmp_ui(n, 2) == 0)
	{
		clearAll(a, n, n_1, resultatPgcd, resultatMod, resultatCalcul, puis);
		//printf("Ok ici %d\n", p);
		fclose(fichier);

		return 1;
	}
	else
	{
		do
		{
			mpz_urandomm(a, state, n); gmp_printf("Ici notre a vaut a = %Zd et n = %Zd\n", a, n);
		}while(mpz_cmp_ui(a, 0) == 0 || mpz_cmp_ui(a, 1) == 0);
		//gmp_printf("p = %d ! et a = %Zd , n = %Zd, n_1 = %Zd\n",p, a, n, n_1);
		mpz_gcd(resultatPgcd, a, n);
		// gmp_printf("resultatPgcd = %Zd\n", resultatPgcd);
		mpz_powm(resultatMod, a, n_1, n);
		//gmp_printf("resultatMod = %Zd\n", resultatMod);
		if(mpz_cmp_ui(resultatPgcd, 1) == 0 && mpz_cmp_ui(resultatMod, 1) == 0)	// Si pgcd(a,b) = 1 et a^(n-1) = 1 mod n
		{
			facteursPremiers fact = factorisation(p - 1);
			i = 0;
			while(i < fact.longueur)
			{printf("ici i = %d et fact.longueur = %d et facteurs = %d\n", i, fact.longueur, fact.facteurs[i]);
				if(certificatPratt(fact.facteurs[i], state) == 1)
				{
					mpz_cdiv_q_ui(puis, n_1, fact.facteurs[i]);gmp_printf("puis = %Zd\n", puis);
					mpz_powm(resultatCalcul, a, puis, n);
					if(mpz_cmp_ui(resultatCalcul, 1) == 0)		// Si resultatCalcul = 1
					{
						gmp_printf("resultatCalcul = %Zd\n", resultatCalcul);
						clearAll(a, n, n_1, resultatPgcd, resultatMod, resultatCalcul, puis);
						fclose(fichier);

						return certificatPratt(p, state);		// On relance un certificat pour choisir un a aléatoire différent
					}
				}
				else
				{
					printf("Erreur : Un nombre dans la factorisation n'est pas premier.\n");
					clearAll(a, n, n_1, resultatPgcd, resultatMod, resultatCalcul, puis);
					fclose(fichier);
					exit(1);
				}
				i = i + 1;
			}
			clearAll(a, n, n_1, resultatPgcd, resultatMod, resultatCalcul, puis);
			fclose(fichier);

			return 1;
		}
		else
		{
			clearAll(a, n, n_1, resultatPgcd, resultatMod, resultatCalcul, puis);
			fclose(fichier);

			return 0;
		}	
	}
	clearAll(a, n, n_1, resultatPgcd, resultatMod, resultatCalcul, puis);
	fclose(fichier);

	return 1;
}
