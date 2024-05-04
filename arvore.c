#include <stdio.h>
#include <stdlib.h>
#include <time.h> 


typedef struct No {
	int dado;
	struct No *esq , *dir , *pai;
} No;

typedef No * p_no;

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
		novo->chave = chave;
		return novo;
	}

	if (chave < raiz->chave)
		raiz->esq = inserir(raiz->esq, chave);
	else
		raiz->dir = inserir(raiz->dir, chave);
	
	return raiz;
}

p_no buscar(p_no raiz, int value)
{
    p_no n;

    if(raiz != NULL)
    {
        if(raiz->dado == value)
          return raiz;

        n = buscar(raiz->esq, value);
        if(n != NULL)
          return n;

        n = buscar(raiz->dir, value);
        if(n != NULL)
          return n;

        return NULL;
    }
}

p_no buscar_iterativo(p_no raiz , int chave) 
{
	while (raiz != NULL && chave != raiz ->chave)
	{
		if (chave < raiz ->chave)
			raiz = raiz ->esq;
		else
			raiz = raiz ->dir;
	}
	
	return raiz;
}


int main()
{
	return 0;
}