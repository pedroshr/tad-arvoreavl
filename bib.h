
struct cliente {
	int codigo;
	char nome[30];
	int idade;
	float peso;
	float altura;
};
typedef struct cliente Cliente;

struct node {
	Cliente cliente;
	struct node *esquerda;
	struct node *direita;
	int altura;
};
typedef struct node Node;


Node *inicializar();
Node *criar_node(Cliente pCliente);
Cliente criar_cliente();
Node* rotacionar_esquerda(Node *node);
Node* rotacionar_direita(Node *node);
Node* rotacionar_direita_esquerda(Node *node);
Node* rotacionar_esquerda_direita(Node *node);
void imprimir_cliente(Cliente pCliente);
void imprimir_arvore_ordenado(Node *raiz);
Node *inserir(Node *raiz,Cliente pCliente);
Node* balanceamento(Node *node);
Node *buscar_elemento_imprimir(Node *raiz, int cod);
Node *buscar_elemento_editar(Node *raiz, int cod);
void liberar_arvore(Node *raiz);
int quantidade_elementos(Node *raiz);
int altura_arvore(Node *raiz);
int altura_node(Node *node);
int fator_de_balanceamento(Node *node);
int maior_altura(int altura_a, int altura_b);
Node *excluir(Node *raiz, int cod);
void imprimir_estrutura_arvore(Node *raiz, int nivel);
void limpar_buffer();
void limpar_tela();





