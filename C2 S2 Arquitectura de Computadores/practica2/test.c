#include <stdlib.h>
#include <stdio.h>

int main()
{
	int **a = malloc(2598347983479485596*sizeof(double*));
	for(int i =0;i<255;i++)
	{
		a[i]=malloc(1440*sizeof(double));
	}

	return 0;
}
