#include "pocklington.h"

#define LIMIT sizeof(primes) / sizeof(unsigned int)

const unsigned int primes[] = {
  2,3,5,7,11,13,17,19,23,29,
  31,37,41,43,47,53,59,61,67,71,
  73,79,83,89,97,101,103,107,109,113,
  127,131,137,139,149,151,157,163,167,173,
  179,181,191,193,197,199,211,223,227,229,
  233,239,241,251,257,263,269,271,277,281,
  283,293,307,311,313,317,331,337,347,349,
  353,359,367,373,379,383,389,397,401,409,
  419,421,431,433,439,443,449,457,461,463,
  467,479,487,491,499,503,509,521,523,541,
  547,557,563,569,571,577,587,593,599,601,
  607,613,617,619,631,641,643,647,653,659,
  661,673,677,683,691,701,709,719,727,733,
  739,743,751,757,761,769,773,787,797,809,
  811,821,823,827,829,839,853,857,859,863,
  877,881,883,887,907,911,919,929,937,941,
  947,953,967,971,977,983,991,997,
};

int pocklington(mpz_t n, facteursPremiers *f) {
	mpz_t n_; //n-1
	mpz_t tmp;
	int i, i_min, j, res;
	
	res = -1;
	
	mpz_init(n_);
	mpz_init(tmp);
	
	//n_ = n-1
	mpz_set(n_, n);
	mpz_sub_ui(n_, n_, 1);
	
	//Il faut que q > sqrt(n)-1
	mpz_sqrt(tmp, n);
	mpz_sub_ui(tmp, tmp, 1);
	i_min = 0;
	for (i = 0; i < f->longueur; i++) {
		if (mpz_cmp_ui(tmp, f->facteurs[i]) < 0) {
			i_min = i;
			break;
		}
	}
	
	for (j = 0; j < LIMIT; j++) {
		//TODO: a = primes[j]
		//TODO: Verifier si a = n (si oui, n est premier)
		//TODO: Verifier si a|n (si oui, n n'est pas premier)
		//TODO: test de Fermat entre a et n (si non, n n'est pas premier)
		for (i = i_min; i < f->longueur; i++) {
			//TODO: q = f[i]
			//TODO: Verifier si pgcd(a^((n-1)/q)-1, n) = 1 (si oui, n est premier)
		}
	}
	
	mpz_clear(n_);
	mpz_clear(tmp);
}
