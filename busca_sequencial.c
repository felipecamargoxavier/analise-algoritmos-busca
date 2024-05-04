#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

int writeFile(char *sArquivo, const char * message)
{
	if(!sArquivo)
        return -1;

	FILE* arquivo = fopen(sArquivo,"w");

	if(arquivo == NULL)
        return -4;

    fprintf(arquivo, message);

    fclose(arquivo);
    return +1;
}

int appendFile(char *sArquivo, const char * message)
{
	if(!sArquivo)
        return -1;

    FILE* arquivo = fopen(sArquivo,"a");

    if(arquivo == NULL)
        return -4;

    fprintf(arquivo, message);

    fclose(arquivo);
    return +1;
}

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

int buscaSequencial(int *v, int tam, int chave)
{
	for(int i = 0; i<tam; i++)
	{
		if(v[i] == chave)
			return i;
	}

	return -1;
}

void testeAleatorio(char *sArquivo, int *v, int tam, int nteste, int piorCaso)
{	
	int k;
	int ncomp = 0;
	int chave;
	clock_t start, end;
	double cpu_time_used;
	char msg[100];

	writeFile(sArquivo, "TESTE; INDICE; CHAVE; COMP; TEMPO(s); TEMPO(us);\r\n");

	srand(time(NULL)); 

	k = tam-1;

	for(int i = 0; i < nteste; i++)
	{
		if(piorCaso != 1)
			k = rand() % tam;
		
		chave = v[k];

		start = clock();

		ncomp = buscaSequencial(v, tam, chave);
		ncomp++;

		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

		sprintf(msg,"%d; %d; %d; %d; %f; %.2f;\r\n", i, k, chave, ncomp, cpu_time_used, cpu_time_used*1000000);
		appendFile(sArquivo, msg);
	}
}


int main()
{
	char file_name[100];
	int tam, nteste, op;

	printf("cenario de teste: ");
	scanf("%d", &tam);
	printf("numero de testes: ");
	scanf("%d", &nteste);
	printf("[0] cenario aleatorio\n\r");
	printf("[1] cenario pior caso\n\r");
	printf("opcao: ");
	scanf("%d", &op);

	if(tam <= 0 || nteste <= 0)
		return -1;

	int *vread = malloc( tam * sizeof(int));
    sprintf(file_name,"ordenacao_%d.txt", tam);
	lerNumeros(file_name, vread, tam);

	sprintf(file_name,"cenario_teste_%d.csv", tam);
	testeAleatorio(file_name, vread, tam, nteste, op);

	


	free(vread);

	return 0;
}