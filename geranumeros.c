#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

//#define PRINT_VETOR
//#define LER_VETOR

int lerNumeros(char *sArquivo, int *v, int tam)
{
	if(!sArquivo || v == NULL)
        return -1;

    FILE* arquivo = fopen(sArquivo,"r");

    if(arquivo == NULL)
        return -4;

    int i = 0;
    while (!feof(arquivo) && i < tam) 
    {
    	fscanf(arquivo, "%d, ", &v[i]);
    	i++;
    }

    fclose(arquivo);
    return +1;
}

int salvarNumeros(char *sArquivo, int *v, int tam)
{
    if(!sArquivo)
        return -1;

    FILE* arquivo = fopen(sArquivo,"wb");

    if(arquivo == NULL)
        return -4;

    int i;
    int numero;

    for(i=0; i<tam; i++)
    	fprintf(arquivo,"%d, ", v[i]);

    fclose(arquivo);
    return +1;
}

void initVector(int *v, int tam)
{
	for(int i = 0; i < tam; i++)
		v[i] = i;
}

void printVector(int *v, int tam)
{
	for(int i = 0; i<tam; i++)
		printf("v[%d] = %d\n", i, v[i]);
}

void shuffle(int *v, int tam)
{
	srand(time(NULL)); 

	int k;
	int aux;

	for(int i=0; i<(tam/2); i++)
	{
		k = rand() % tam;

		aux = v[i];
		v[i] = v[k];
		v[k] = aux;
	}
}

int main()
{
	int tam;

	printf("informe o tamanho do vetor: ");
	scanf("%d", &tam);
	
	if(tam <= 0)
		return -1;
	int *v = malloc( tam * sizeof(int));

	initVector(v, tam);
	shuffle(v, tam);

	char file_name[100];
    sprintf(file_name,"ordenacao_%d.txt", tam);

    if(salvarNumeros(file_name, v, tam) == +1)
    {
    	printf("%d numeros gerados com sucesso.\n", tam);
        printf("nome arquivo: %s\n", file_name);
    }
    else
    	printf("erro ao gerar numeros!\n");
	
	#ifdef PRINT_VETOR
		printVector(v, tam);
	#endif

	#ifdef LER_VETOR
		int *vread = malloc( tam * sizeof(int));

		lerNumeros(file_name, vread, tam);

		printf("\n\nVetor lido:\n");
		printVector(vread, tam);

		free(vread);
	#endif


	free(v);
	
	return 0;
}