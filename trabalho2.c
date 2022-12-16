#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Page {
	int numero;
	struct Page *next;	
}Page;

char *arquivo;
int totalWSL, usadoWSL=0, pagina;
FILE *file;
Page *first, *last;

//insere as paginas no fim da fila
void Cria(int value){
	Page *novo = (Page*)malloc(sizeof(Page));
	novo->numero = value;
	novo->next = NULL;
	
	if(usadoWSL == 0){
		first = novo;
		last = first;
	}
	else {
		last->next = novo;
		last = novo;
	}

	if(usadoWSL < totalWSL)
		usadoWSL++;
}

//insere a pagina no final e retira o primeiro elemento
void LRU(int pagina){
	Cria(pagina);
    printf("O endereco %d SAI na memoria\n", first->numero);
	first = first->next;
}

// procura e pagina na memoria, se a pagina ta na memoria muda ela de posicao
bool Find(int pagina){
	Page *tmp = first, *ant=NULL;
	while(tmp != NULL){
		if(tmp->numero == pagina){
			if(ant != NULL){
				if(tmp->next != NULL)
					ant->next = tmp->next;
			}
			else
				first = first->next;
			last->next = tmp;
			last = tmp;
			tmp->next = NULL;
			printf("O endereco %d ESTA na memoria\n", pagina);
			return true;
		}
		ant = tmp;
		tmp = tmp->next;
	}
}

// se ainda tem espaco vazio apenas insere se nao insere no final e retira o primeiro elemento
void WSL(int pagina){
	if(usadoWSL < totalWSL){
		Cria(pagina);
	}
	else{
		LRU(pagina);
	}
}

void PrintFila() {
  Page *aux = (Page*)malloc(sizeof(Page));
  aux = first;

  while (aux != NULL){
    printf("%d ", aux->numero); 
    aux = aux->next;
  }
  printf("\n");
}

int main(){
	arquivo = "entrada.txt"; 
	printf("Working Ser List: \n");
	scanf("%d", &totalWSL);

	file = fopen(arquivo, "r");
	printf("\nINICIO SIMULADOR\n");
	while(fscanf(file, "%d", &pagina)!=EOF){
		if(!Find(pagina)){
			WSL(pagina);
		}
		PrintFila();
	}
		
	return 0;
}