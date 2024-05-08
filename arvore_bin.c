#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

typedef struct No {
	int dado;
	struct No *esq , *dir;
} No;

typedef No * p_no;

void percurso_em_largura(p_no raiz) 
{
	p_fila f;
	f = criar_fila();
	enfileirar(f, raiz);

	while (!fila_vazia(f)) 
	{
		raiz = desenfileirar(f);

		if (raiz) 
		{
 			enfileirar(f, raiz->esq);
			enfileirar(f, raiz->dir);
			printf("%d ", raiz->dado); /* visita raiz */
		}
	}
	
	destruir_fila(f);
}

p_no criar_arvore(int x) 
{
    p_no tree = malloc(sizeof(No));
    tree->dado = x;
    tree->esq = NULL;
    tree->dir = NULL;
    return tree;
}

int getaltura(p_no raiz) 
{
	int h_esq, h_dir;
	
	if (raiz == NULL)
		return 0;
	
	h_esq = getaltura(raiz->esq);
	h_dir = getaltura(raiz->dir);
	
	return 1 + (h_esq > h_dir ? h_esq : h_dir);
}


void destruir_arvore(p_no raiz)
{
    if(raiz != NULL)
    {
        destruir_arvore(raiz->esq);
        destruir_arvore(raiz->dir);
        free(raiz);
    }
}

p_no inserir(p_no raiz , int chave) 
{
	p_no novo;

	if (raiz == NULL) 
	{
		novo = malloc(sizeof(No));
		novo->esq = NULL;
		novo->dir = NULL;
		novo->dado = chave;
		return novo;
	}

	if (chave < raiz->dado)
		raiz->esq = inserir(raiz->esq, chave);
	else
		raiz->dir = inserir(raiz->dir, chave);
	
	return raiz;
}

int buscar_iterativo(p_no raiz , int chave) 
{
	int comp = 0;

	while (raiz != NULL && chave != raiz->dado)
	{
		comp++;

		if (chave < raiz->dado)
			raiz = raiz->esq;
		else
			raiz = raiz->dir;
	}
	
	return comp;
}

void print(p_no raiz)
{
    if(raiz != NULL)
    {
        printf("%d \n", raiz->dado);
        print(raiz->esq);
        print(raiz->dir);
    }
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

p_no lerNumeros(char *sArquivo, int tam)
{
	int value;

	if(!sArquivo)
        return NULL;

    FILE* arquivo = fopen(sArquivo,"r");

    if(arquivo == NULL)
        return NULL;

    fscanf(arquivo, "%d, ", &value);
    p_no tree = criar_arvore(value);

    int i = 0;
    while (!feof(arquivo) && i < (tam-1)) 
    {
    	fscanf(arquivo, "%d, ", &value);
    	inserir(tree, value);
    	i++;
    }

    fclose(arquivo);
    return tree;
}

void testeAleatorio(char *sArquivo, p_no tree, int tam, int nteste, int piorCaso)
{	
	int ncomp = 0;
	int chave;
	clock_t start, end;
	double cpu_time_used;
	char msg[100];

	writeFile(sArquivo, "TESTE; CHAVE; COMP; TEMPO(s); TEMPO(us);\r\n");

	srand(time(NULL)); 

	for(int i = 0; i < nteste; i++)
	{
		chave = rand() % tam;
		
		start = clock();

		ncomp = buscar_iterativo(tree, chave);

		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

		sprintf(msg,"%d; %d; %d; %f; %.2f;\r\n", i, chave, ncomp, cpu_time_used, cpu_time_used*1000000);
		appendFile(sArquivo, msg);
	}
}


int main()
{
	char file_name[100];
	int tam, nteste, op;
	p_no tree;

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
    tree = lerNumeros(file_name, tam);

    sprintf(file_name,"cenario_teste_%d.csv", tam);
	testeAleatorio(file_name, tree, tam, nteste, op);

	//printf("\nARVORE:\n");
	//print(tree);

	int altura = getaltura(tree);
	printf("\nALTURA ARVORE: %d\n", altura);

	destruir_arvore(tree);

	return 0;
}