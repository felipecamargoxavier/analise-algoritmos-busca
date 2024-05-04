#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

typedef struct No 
{
 	int dado;
 	struct No *prox;
} No;

typedef struct No* p_no;

p_no criar_lista () 
{
	return NULL;
}

/*
void destruir_lista(p_no lista) 
{
	if(lista != NULL)
	{
		destruir_lista(lista->prox);
		free(lista);
	}
}
*/

void destruir_lista(p_no lista, int tam) 
{
  if (lista != NULL) 
  {
  	p_no atual = lista;
  	p_no prox;

    for (int i=0; i < tam; i++) 
    {
    	prox = atual->prox;
    	free(atual);
    	atual = prox;
    } 
  }
}

p_no adicionar_elemento(p_no lista , int x)
{
	p_no novo;
	novo = malloc(sizeof(struct No));
	novo->dado = x;
	novo->prox = lista;
	return novo;
}

p_no lerNumeros(char *sArquivo, int tam, p_no lista)
{
	if(!sArquivo)
        return NULL;

    FILE* arquivo = fopen(sArquivo,"r");

    if(arquivo == NULL)
        return NULL;

    int value;
    int i = 0;

    while (!feof(arquivo) && i < tam) 
    {
    	fscanf(arquivo, "%d, ", &value);
    	lista = adicionar_elemento(lista, value);
    	i++;
    }

    fclose(arquivo);

    printf("\nnumeros lidos com sucesso\n");

    return lista;
}

void imprime(p_no lista) 
{
	printf("\nIMPRIME LISTA LIGADA:\n");

	p_no atual;
	for (atual = lista; atual != NULL; atual = atual->prox)
		printf("%d\n", atual->dado);
}

int getPiorcaso(p_no lista)
{
	int chave = -1;

	p_no atual;
	for (atual = lista; atual != NULL; atual = atual->prox)
		chave = atual->dado;

	return chave;
}

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

int buscaSequencial(p_no lista, int chave)
{
	int comp = 0;

	p_no atual;
	for (atual = lista; atual != NULL; atual = atual->prox)
	{
		comp++;

		if(atual->dado == chave)
			return comp;
	}

	return -1;
}


void testeAleatorio(char *sArquivo, p_no lista, int tam, int nteste, int piorCaso)
{	
	int ncomp = 0;
	int chave;
	clock_t start, end;
	double cpu_time_used;
	char msg[100];

	writeFile(sArquivo, "TESTE; CHAVE; COMP; TEMPO(s); TEMPO(us);\r\n");

	if(piorCaso == 1)
		chave = getPiorcaso(lista);

	srand(time(NULL)); 

	for(int i = 0; i < nteste; i++)
	{
		if(piorCaso == 0)
			chave = rand() % tam;

		start = clock();

		ncomp = buscaSequencial(lista, chave);

		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

		sprintf(msg,"%d; %d; %d; %f; %.2f;\r\n", i, chave, ncomp, cpu_time_used, cpu_time_used*1000000);
		appendFile(sArquivo, msg);
	}

	printf("teste aleatorio executado\n");
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

    sprintf(file_name,"ordenacao_%d.txt", tam);

    p_no lista;
    lista = criar_lista();
	lista = lerNumeros(file_name, tam, lista);

	sprintf(file_name,"cenario_teste_%d.csv", tam);
	testeAleatorio(file_name, lista, tam, nteste, op);

	//imprime(lista);
	destruir_lista(lista, tam);

	return 0;
}