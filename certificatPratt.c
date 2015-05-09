#include "certificatPratt.h"

/*
Cette fonction utilisable seulement dans ce fichier, libère simplement la mémoire des variables de types mpz_t
utilisés dans la fonction certificatPratt.
*/
static void clearAll(mpz_t a, mpz_t p_1, mpz_t resultatPgcd, mpz_t resultatMod, mpz_t resultatCalcul, mpz_t puis)
{
	mpz_clear(a);
	mpz_clear(p_1);
	mpz_clear(resultatPgcd);
	mpz_clear(resultatMod);
	mpz_clear(resultatCalcul);
	mpz_clear(puis);
}

facteursPremiers factorisation(mpz_t f)
{
	int marqueur = 0, j;
	facteursPremiers fact;
	mpz_t i;
	mpz_t tab[MAXBUF];
	mpz_t racine;
	mpz_t resultatMod;
	mpz_t fCopie;

	mpz_init(resultatMod);
	mpz_init(racine);
	mpz_init_set_ui(i, 2);
	mpz_sqrt(racine, f);
	mpz_init_set(fCopie, f);			// On initialise un fCopie qui est une copie de f (Pour les calculs)
	fact.longueur = 0;
	while(mpz_cmp(racine,i) >= 0)		// Valeur positive ou nulle si racine >= i 
	{
		mpz_mod(resultatMod, fCopie, i);	// resultatMod = fCopie % i
		if(mpz_cmp_ui(resultatMod, 0) == 0)		// Si fCopie % i = 0 (Equivaut à resultatMod = 0)
		{
			while(mpz_cmp_ui(resultatMod, 0) == 0)		// Tant que fCopie % i = 0 (Equivaut à resultatMod = 0)
			{
				mpz_divexact(fCopie, fCopie, i);		// fCopie = fCopie / i
				mpz_mod(resultatMod, fCopie, i);		// resultatMod = fCopie % i
			}
			fact.longueur ++;				// On augmente le nombre de facteur
			mpz_init_set(tab[marqueur], i);	// On stocke le facteur en question dans un tableau
			marqueur++;
		}
		mpz_add_ui(i, i, 1);		// Equivaut à i = i + 1
	}
	if(fact.longueur == 0)
	{
		fact.longueur = 1;
		mpz_init_set(tab[marqueur], i);
	}
	else if(mpz_cmp_ui(fCopie, 1) > 0)		// Si fCopie ne vaut pas 1, cela veut dire qu'elle contient encore un facteur
	{
		fact.longueur++;
		mpz_init_set(tab[marqueur], fCopie);// On rajoute le dernier facteur dans le tableau
	}
	fact.facteurs = malloc(fact.longueur * sizeof(mpz_t));	// On alloue la mémoire pour la variable de type facteursPremiers
	//printf("Nombre de facteurs : %d\n", fact.longueur);
	for(j = 0; j < fact.longueur; j++)		
	{
		mpz_init_set(fact.facteurs[j], tab[j]);		// On rempli le tableau fact.facteurs[i]
		//gmp_printf("Facteur %d = %Zd\n",j , fact.facteurs[j]);
	}
	mpz_clear(i);
	for(j = 0; j < marqueur; j++)
		mpz_clear(tab[j]);
	mpz_clear(racine);
	mpz_clear(resultatMod);
	mpz_clear(fCopie);

	return fact;
}

void clearFacteursPremiers(facteursPremiers f)
{
	int i;

	for (i = 0; i < f.longueur; i++)
		mpz_clear(f.facteurs[i]);
	free(f.facteurs);
}

int certificatPratt(mpz_t p, gmp_randstate_t state)
{
	FILE *fichier = NULL;
	mpz_t a;		// Variable qui sera défini aléatoirement
	mpz_t p_1;		// Variable qui sera initialisée à p - 1
	mpz_t resultatPgcd, resultatMod, resultatCalcul;	// Variables qui contiendront des résultats de calculs
	mpz_t puis;		// Variable qui contiendra un résultat d'un calcul
	int i;

	mpz_init(a);
	mpz_init(resultatPgcd);
	mpz_init(resultatMod);
	mpz_init(resultatCalcul);
	mpz_init(puis);
	mpz_init_set(p_1, p);
	mpz_sub_ui(p_1, p_1, 1);
	fichier = fopen("nombresPremiers.txt", "r+");
	if(fichier == NULL)
	{
		printf("Erreur lors de l'ouverture du fichier nombresPremiers.txt.\n");

		exit(1);
	}
	if(mpz_cmp_ui(p, 2) == 0)		// Si p = 2 la fonction renvoie 1
	{
		clearAll(a, p_1, resultatPgcd, resultatMod, resultatCalcul, puis);
		fclose(fichier);

		return 1;
	}
	else	// Sinon on suit les étapes du certificat
	{
		do
		{
			mpz_urandomm(a, state, p); 
			//gmp_printf("a = %Zd et p = %Zd\n", a, p);
		}while(mpz_cmp_ui(a, 0) == 0 || mpz_cmp_ui(a, 1) == 0);	// On choisi un nouveau a tant qu'il vaut 0 ou 1
		mpz_gcd(resultatPgcd, a, p);		// resultatPgcd = pgcd(a,p)
		mpz_powm(resultatMod, a, p_1, p);	// resultatMod = a^(p-1) % p
		if(mpz_cmp_ui(resultatPgcd, 1) == 0 && mpz_cmp_ui(resultatMod, 1) == 0)	// Si pgcd(a,b) = 1 et a^(n-1) = 1 mod n
		{
			facteursPremiers fact = factorisation(p_1);		// On stocke dans fact la factorisation de p - 1
			i = 0;
			while(i < fact.longueur)	// Pour chaque facteur
			{
				if(certificatPratt(fact.facteurs[i], state) == 1)	// Recursivité : On éxécute un certificat de Pratt sur chaque facteur
				{
					mpz_cdiv_q(puis, p_1, fact.facteurs[i]);	// puis = (p-1)/fact.facteurs[i]
					mpz_powm(resultatCalcul, a, puis, p);		// resultatCalcul = a^puis % p
					if(mpz_cmp_ui(resultatCalcul, 1) == 0)		// Si resultatCalcul = 1 (Cas rare)
					{
						gmp_printf("On rentre dans le rare cas où la 3eme condition n'est pas vérifiée. Test avec un a différent...\n");
						clearAll(a, p_1, resultatPgcd, resultatMod, resultatCalcul, puis);
						clearFacteursPremiers(fact);
						fclose(fichier);

						return certificatPratt(p, state);		// On relance un certificat pour choisir un a aléatoire différent
					}
				}
				else	// Si un des facteurs n'est pas premier, on ne peut rien conclure: Il y a eu un problème lors de la factorisation
				{
					printf("Erreur : Un nombre dans la factorisation n'est pas premier.\n");
					clearAll(a, p_1, resultatPgcd, resultatMod, resultatCalcul, puis);
					clearFacteursPremiers(fact);
					fclose(fichier);

					return -1;
				}
				i = i + 1;
			}
			clearAll(a, p_1, resultatPgcd, resultatMod, resultatCalcul, puis);
			clearFacteursPremiers(fact);
			fclose(fichier);

			return 1;	// Si tous ces tests sont passés, cela veut dire que le nombre est premier.
		}
		else 	// Sinon si pgcd(a,b) != 1 ou a^(n-1) != 1 mod n
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
