#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	int choix;

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
			
		}
		else if(choix == 2)
		{

		}
		else if(choix == 3)
		{

		}
		else if(choix == 4)
		{

		}
	}while(choix == 1 || choix == 2 || choix == 3 || choix == 4);
	

	return 0;
}