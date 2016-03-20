#ifndef Rand_Poids_H
#define Rand_Poids_H

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>


unsigned int poidsFaible( unsigned int alea, int nbDeBit)
{
		/*int nbDigit = pow(2,nbDeBit) - 1;
		int  num = 32424;
		char hex[5];
		sprintf(hex, "%x", num);
		*/
		
		return alea & 0x0F;
}

unsigned int poidsFort(unsigned int alea, int nbDeBit)
{
	alea = alea >> 27;  		// attention il faut décaler de 27 bit car randMax est sur 31 bits.
	return alea & 0x0F;
}

void generation (int longueur, int poidsFai, int * val)
{	
	FILE *fp;
	fp = freopen("Rand.txt", "w+", stdout);		// ouvertur du fichier
	unsigned int alea;
	int i;
	if (poidsFai)
	{
		for (i = 0; i < longueur; i ++)
		{
			alea = rand();
			alea = poidsFaible(alea,4);
			printf("%d\t",alea );
			val[i] = alea;
		}
	}
	else
	{
		for (i = 0; i < longueur; i ++)
		{
			alea = rand();
			alea = poidsFort(alea,4);
			printf("%d\t",alea );
			val[i] = alea;
		}
	}
	fclose(fp);
} 


#endif
