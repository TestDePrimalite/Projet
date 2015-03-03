#include "certificatPratt.h"

int certificatPratt(int p)
{
	mpz_t a;
	mpz_t n;
	mpz_t n_1;
	mpz_t resultatPgcd;
	mpz_t resultatMod;

	mpz_init_set_ui(n, p);
	mpz_init_set_ui(a, 2);
	mpz_init_set_ui(n_1, p - 1);
	mpz_init(resultatPgcd);
	mpz_init(resultatMod);
	if(mpz_cmp_ui(n, 2))
		return 1;
	else
	{
		mpz_gcd(resultatPgcd, a, n);
		mpz_powm(resultatMod, a, n_1, n);
		if(mpz_cmp_ui(resultatPgcd, 1) == 0 && mpz_cmp_ui(resultatMod, 1) == 0)	// Si pgcd(a,b) = 1 et a^(n-1) = 1 mod n
		{

		}
	}

	return 1;
}