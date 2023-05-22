#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "bib.h"

Node *inicializar() {
	return NULL;
};

Node *criar_node(Cliente pCliente) {
	Node *node=(Node*) malloc(sizeof(Node));
	node->cliente.codigo=pCliente.codigo;
	strcpy(node->cliente.nome, pCliente.nome);
	node->cliente.altura=pCliente.altura;
	node->cliente.peso=pCliente.peso;
	node->cliente.idade=pCliente.idade;
	node->esquerda=NULL;
	node->direita=NULL;
	node->altura=0;
	return node;
};

Cliente criar_cliente() {
	Cliente pCliente;
	printf("Digite o codigo:");
	scanf("%d", &pCliente.codigo);
	limpar_buffer();
	printf("Digite o nome:");
	fgets(pCliente.nome, 31, stdin);
	pCliente.nome[strcspn(pCliente.nome, "\n")] = 0;
	printf("Digite a idade:");
	scanf("%d", &pCliente.idade);
	printf("Digite a altura(ex: 1.70):");
	scanf("%f", &pCliente.altura);
	limpar_buffer();
	printf("Digite o peso(ex: 64.7):");
	scanf("%f", &pCliente.peso);
	limpar_buffer();
	return pCliente;
};

Node* rotacionar_esquerda(Node *node) {
	Node *desbalanceado, *filho;

	desbalanceado=node->direita;
	filho=desbalanceado->esquerda;

	desbalanceado->esquerda=node;
	node->direita=filho;

	node->altura= maior_altura(altura_node(node->esquerda),altura_node(node->direita)) + 1;
	desbalanceado->altura= maior_altura(altura_node(desbalanceado->esquerda),altura_node(desbalanceado->direita)) + 1;

	return desbalanceado;
};

Node* rotacionar_direita(Node *node) {
	Node *desbalanceado, *filho;

	desbalanceado=node->esquerda;
	filho=desbalanceado->direita;

	desbalanceado->direita=node;
	node->esquerda=filho;

	node->altura= maior_altura(altura_node(node->esquerda),altura_node(node->direita)) + 1;
	desbalanceado->altura= maior_altura(altura_node(desbalanceado->esquerda),altura_node(desbalanceado->direita)) + 1;

	return desbalanceado;
};

Node* rotacionar_direita_esquerda(Node *node) {
	node->direita=rotacionar_direita(node->direita);
	return rotacionar_esquerda(node);
};

Node* rotacionar_esquerda_direita(Node *node) {
	node->esquerda=rotacionar_esquerda(node->esquerda);
	return rotacionar_direita(node);
};

void imprimir_cliente(Cliente pCliente) {
	printf("\n");
	printf("Codigo: %d\n", pCliente.codigo);
	printf("Nome: %s\n", pCliente.nome);
	printf("Idade: %d\n", pCliente.idade);
	printf("Altura: %.2f\n", pCliente.altura);
	printf("Peso: %.2f\n", pCliente.peso);
};

void imprimir_arvore_ordenado(Node *raiz) {
	if(raiz!=NULL) {
		imprimir_cliente(raiz->cliente);
		imprimir_arvore_ordenado(raiz->esquerda);
		imprimir_arvore_ordenado(raiz->direita);
	}
};

Node *inserir(Node *raiz,Cliente pCliente) {
	if(raiz==NULL) {
		return criar_node(pCliente);

	} else {
		if (pCliente.codigo > raiz->cliente.codigo) {
			raiz->direita = inserir(raiz->direita, pCliente);
		} else if (pCliente.codigo < raiz->cliente.codigo) {
			raiz->esquerda = inserir(raiz->esquerda, pCliente);
		}
	}
	raiz->altura= maior_altura(altura_node(raiz->esquerda),altura_node(raiz->direita)) + 1;
	raiz=balanceamento(raiz);
	return raiz;
};

Node* balanceamento(Node *node) {
	int fb=fator_de_balanceamento(node);
	if(fb<-1 && fator_de_balanceamento(node->direita)<=0) {
		node=rotacionar_esquerda(node);
	}
	if(fb>1 && fator_de_balanceamento(node->esquerda)>=0) {
		node=rotacionar_direita(node);
	}
	if(fb>1 && fator_de_balanceamento(node->esquerda)<0) {
		node=rotacionar_esquerda_direita(node);
	}
	if(fb<-1 && fator_de_balanceamento(node->direita)>0) {
		node=rotacionar_direita_esquerda(node);
	}
	return node;
};

Node *buscar_elemento_imprimir(Node *raiz, int cod) {
	if(raiz==NULL) {
		limpar_tela();
		printf("\nCodigo nao encontrado!\n\n");
		return NULL;
	} else {
		if (cod == raiz->cliente.codigo) {
			printf("Codigo encontrado!\n\n");
			printf("Codigo: %d\n", raiz->cliente.codigo);
			printf("Nome: %s\n", raiz->cliente.nome);
			printf("Idade: %d\n", raiz->cliente.idade);
			printf("Altura: %.2f\n", raiz->cliente.altura);
			printf("Peso: %.2f\n", raiz->cliente.peso);
			printf("\n");
			return raiz;
		} else if (cod > raiz->cliente.codigo) {
			return buscar_elemento_imprimir(raiz->direita, cod);
		} else {
			return buscar_elemento_imprimir(raiz->esquerda, cod);
		}
	}
};

Node *buscar_elemento_editar(Node *raiz, int cod) {


	if(raiz==NULL) {
		limpar_tela();
		printf("\n\nCodigo nao encontrado!\n\n");
		return NULL;
	} else {
		if (cod == raiz->cliente.codigo) {
			Cliente pCliente;
			pCliente.codigo = cod;
			limpar_buffer();
			printf("\nDigite os valores que irao substituir os antigos...\n");
			printf("Digite o nome:");
			fgets(pCliente.nome, 31, stdin);
			pCliente.nome[strcspn(pCliente.nome, "\n")] = 0;
			printf("Digite a idade:");
			scanf("%d", &pCliente.idade);
			printf("Digite a altura(ex: 1.70):");
			scanf("%f", &pCliente.altura);
			limpar_buffer();
			printf("Digite o peso(ex: 64.7):");
			scanf("%f", &pCliente.peso);
			limpar_buffer();
			raiz->cliente=pCliente;

			printf("\n\nCodigo encontrado e alterado!\n");
			printf("Codigo: %d\n", raiz->cliente.codigo);
			printf("Nome: %s\n", raiz->cliente.nome);
			printf("Idade: %d\n", raiz->cliente.idade);
			printf("Altura: %.2f\n", raiz->cliente.altura);
			printf("Peso: %.2f\n", raiz->cliente.peso);
			printf("\n");
			return raiz;
		} else if (cod > raiz->cliente.codigo) {
			return buscar_elemento_editar(raiz->direita, cod);
		} else {
			return buscar_elemento_editar(raiz->esquerda, cod);
		}
	}
	raiz->altura= maior_altura(altura_node(raiz->esquerda),altura_node(raiz->direita)) + 1;
	balanceamento(raiz);
};

void liberar_arvore(Node *raiz) {
	if(raiz==NULL) {
		liberar_arvore(raiz->esquerda);
		liberar_arvore(raiz->direita);
		free(raiz);
	}
};

int quantidade_elementos(Node *raiz) {
	if (raiz==NULL) {
		return 0;
	} else {
		return 1 + quantidade_elementos(raiz->esquerda) + quantidade_elementos(raiz->direita);
	}
};

int altura_arvore(Node *raiz) {
	int esquerda, direita;
	if(raiz==NULL) {
		return -1;
	} else {
		esquerda = altura_arvore(raiz->esquerda);
		direita = altura_arvore(raiz->direita);
		if (esquerda < direita) {
			return direita + 1;
		} else {
			return esquerda + 1;
		}
	}
};

int altura_node(Node *node) {
	if(node==NULL) {
		return -1;
	} else {
		return node->altura;
	}
};

int fator_de_balanceamento(Node *node) {
	return altura_node(node->esquerda) - altura_node(node->direita);
};

int maior_altura(int altura_a, int altura_b) {
	if(altura_a > altura_b) {
		return altura_a;
	} else {
		return altura_b;
	}
};

Node *excluir(Node *raiz, int cod) {
	if(raiz==NULL) {
		printf("Valor nao encontrado!\n");
		return NULL;
	} else {
		if (raiz->cliente.codigo == cod) {
			if (raiz->esquerda==NULL && raiz->direita==NULL) {
				free(raiz);
				printf("Elemento removido!\n");
				return NULL;
			} else {
				if (raiz->esquerda!=NULL && raiz->direita!=NULL) {
					Node *aux=raiz->esquerda;
					Cliente aux_cliente;
					while(aux->direita!=NULL) {
						aux=aux->direita;
					}

					aux_cliente=raiz->cliente;
					raiz->cliente=aux->cliente;
					aux->cliente=aux_cliente;

					raiz->esquerda=excluir(raiz->esquerda, cod);
					return raiz;

				} else {
					Node *aux;
					if (raiz->esquerda!=NULL) {
						aux=raiz->esquerda;
					} else {
						aux=raiz->direita;
					}
					free(raiz);
					printf("Elemento removido!\n");
					return aux;
				}
			}
		} else {
			if (cod < raiz->cliente.codigo) {
				raiz->esquerda = excluir(raiz->esquerda, cod);
			} else {
				raiz->direita = excluir(raiz->direita, cod);
			}
		}
		raiz->altura= maior_altura(altura_node(raiz->esquerda),altura_node(raiz->direita)) + 1;
		raiz=balanceamento(raiz);
		return raiz;
	}
}

void imprimir_estrutura_arvore(Node *raiz, int nivel) {
	int i;
	if(raiz!=NULL) {
		imprimir_estrutura_arvore(raiz->direita, nivel + 1);
		printf("\n\n");
		for(i=0; i<nivel; i++) {
			printf("\t");
		}
		printf("Codigo: %d", raiz->cliente.codigo);
		printf("   Nome: %s", raiz->cliente.nome);
		printf("   Idade: %d", raiz->cliente.idade);
		printf("   Altura: %.2f", raiz->cliente.altura);
		printf("   Peso: %.2f", raiz->cliente.peso);
		imprimir_estrutura_arvore(raiz->esquerda, nivel + 1);
	}
};

void limpar_tela() {
#ifdef __linux__
	system("clear");
#elif _WIN32
	system("cls");
#else
#endif
};

void limpar_buffer() {
	char c;
	while ((c=getchar())!='\n' && c!=EOF);
}
