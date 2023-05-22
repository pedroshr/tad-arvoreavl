#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "bib.h"

int main () {

	int menu=0, loop=0, codigo;
	char nome[30];

	Node *raiz = inicializar();
	Node *buscar = inicializar();
	Node *editar = inicializar();

	Cliente pCliente;

	while (loop==0) {
		limpar_tela();
		printf("\t\t\t\t    Seja bem vindo ao sistema da academia Phisical Boost\n");
		printf("\t\t\t\t\t        O que deseja fazer?\n\n");
		printf("\t\t\t\t\t        1-Incluir\n\n");
		printf("\t\t\t\t\t        2-Buscar e imprimir\n\n");
		printf("\t\t\t\t\t        3-Editar valor de um elemento\n\n");
		printf("\t\t\t\t\t        4-Excluir\n\n");
		printf("\t\t\t\t\t        5-Imprimir todos elementos\n\n");
		printf("\t\t\t\t\t        6-Imprimir quantidade de elementos\n\n");
		printf("\t\t\t\t\t        7-Altura da arvore\n\n");
		printf("\t\t\t\t\t        8-Imprimir com estrutura de arvore\n\n");
		printf("\t\t\t\t\t        9-Sair\n\n");
		printf("\t\t\t\t\t        Escolha uma opcao:\n");
		scanf("%d", &menu);
		while (menu>9 && menu<1) {
			printf("Opcao invalida! Digite novamente:");
			scanf("%d", &menu);
		}

		limpar_tela();
		switch(menu) {
			case 1:
				raiz = inserir(raiz, criar_cliente());
				system("pause");
				break;

			case 2:
				if(raiz==NULL) {
					printf("Arvore vazia!\n");
				} else {
					printf("\nDigite um codigo inteiro para ser buscado:");
					scanf("%d", &codigo);
					buscar_elemento_imprimir(raiz, codigo);
				}
				system("pause");
				break;

			case 3:
				if(raiz==NULL) {
					printf("Arvore vazia!\n");
				} else {
					printf("\nQual codigo voce deseja alterar?");
					scanf("%d", &codigo);
					buscar_elemento_editar(raiz, codigo);
				}
				system("pause");
				break;

			case 4:
				printf("\nARVORE:\n");
				imprimir_arvore_ordenado(raiz);
				printf("\n----------------------\n");

				printf("Digite um codigo inteiro para ser removido:");
				scanf("%d", &codigo);
				raiz = excluir(raiz, codigo);
				system("pause");
				break;

			case 5:
				printf("\n\n");
				if(raiz==NULL) {
					printf("Arvore vazia!\n");
				} else {
					imprimir_arvore_ordenado(raiz);
				}
				printf("\n");
				system("pause");
				break;

			case 6:
				if(quantidade_elementos(raiz)==0) {
					printf("A arvore esta vazia!\n");
				} else {
					printf("\nQuantidade de elementos: %d", quantidade_elementos(raiz));
				}
				printf("\n");
				system("pause");
				break;

			case 7:
				if(altura_arvore(raiz)==-1) {
					printf("A arvore esta vazia!\n");
				} else {
					printf("\nAltura da arvore: %d\n", altura_arvore(raiz));
				}
				printf("\n");
				system("pause");
				break;

			case 8:
				printf("\n\n");
				if(raiz==NULL) {
					printf("Arvore vazia!\n");
				} else {
					imprimir_estrutura_arvore(raiz, 1);
				}
				printf("\n\n\n");
				system("pause");
				break;

			case 9:
				printf("\nPrograma fechando...\n");
				if(raiz!=NULL) {
					liberar_arvore(raiz);
				}
				exit(0);
		}
	}

	return 0;
}
