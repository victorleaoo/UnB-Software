#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Variáveis globais
int origem = 0, destino = 0;
char nomeOrigem[26], nomeDestino[26];
#define M 997

// Estrutura do Item (hash para o nome)
typedef struct Item{
    int chave;
} Item;

Item hash[M];

int hashU (char *v){
	int h, a = 31415, b = 27183;
	
    for(h = 0; *v != '\0'; v++){ // percorrer toda a string
		a = a*b % (M);
		h = (a*h + *v) % M; // *v = ASCII do elemento -- Sempre vai entrar no tamanho da tabela
	}

	return h;
}

// Estrutura do link
typedef struct no *link;

struct no{
    int v;
    link prox;
} no;

// Estrutura do Grafo
typedef struct graph{
    int V, E;
    link *adj;
} graph;

// Estrutura da Edge
typedef struct Edge{
    int u;
    int w;
} Edge;

// Retorna Edge
Edge EDGE(int u, int w){
    return (Edge){u, w};
}

link new(int v, link prox){
    link x = malloc(sizeof(link));

    x->v = v;
    x->prox = prox;

    return x;
}

graph *graphInit(int v){
    graph *G = malloc(sizeof(graph));
    G->V = v;
    G->E = 0;
    G->adj = malloc(v*sizeof(link));

    char nome[26];

    for(int i = 0; i < v; i++){
        scanf(" %s", nome);
        
        // Salvar nomes na hash
        hash[hashU(nome)].chave=i;

        G->adj[i] = NULL;
    }

    return G;
}

void graphInsertE(graph *G, Edge E){
    int u = E.u, w = E.w;

    G->adj[u] = new(w, G->adj[u]);
    G->adj[w] = new(u, G->adj[w]);

    G->E++;

    return;
}

//IMPLEMENTAÇÃO DE FILA

struct Fila {
    int front, rear, size;
    unsigned capacity;
    int* array;
};
 
// Cria Fila
struct Fila* criaFila(unsigned capacity){
    struct Fila* Fila = (struct Fila*)malloc(sizeof(struct Fila));
    Fila->capacity = capacity;
    Fila->front = Fila->size = 0;
 
    Fila->rear = capacity - 1;
    Fila->array = (int*)malloc(
        Fila->capacity * sizeof(int));
    return Fila;
}
 
// Pergunta se está vazia
int filaVazia(struct Fila* Fila){
    return (Fila->size == 0);
}
 
// Enfileira
void enfileira(struct Fila* Fila, int item){
    Fila->rear = (Fila->rear + 1)
                  % Fila->capacity;
    Fila->array[Fila->rear] = item;
    Fila->size = Fila->size + 1;
    return;
}
 
// Desinfileira
int desenfileira(struct Fila* Fila){
    int item = Fila->array[Fila->front];
    Fila->front = (Fila->front + 1)
                   % Fila->capacity;
    Fila->size = Fila->size - 1;
    return item;
}

void graphSearch(graph *G, int s, int *dist){
    int INFINITY = G->V;

    for(int i = 0; i < G->V; i++){
        dist[i] = INFINITY;
    }

    dist[s] = 0;

    struct Fila* f = criaFila(G->V);
    enfileira(f, s);

    while(!filaVazia(f)){
        int v = desenfileira(f);
        for(link a = G->adj[v]; a != NULL; a = a->prox){
            int w = a->v;
            if(dist[w] == INFINITY){
                dist[w] = dist[v]+1;
                enfileira(f, w);
            }
        }
    }
}

int main(void){
    int n, m;

    scanf(" %s %s", nomeOrigem, nomeDestino);
    scanf("%d %d", &n, &m);

    graph *grafo = graphInit(n);

    char nome1[26], nome2[26];
    int aresta1, aresta2;

    for(int i = 0; i < m; i++){
        scanf(" %s %s", nome1, nome2);

        aresta1 = hash[hashU(nome1)].chave;
        aresta2 = hash[hashU(nome2)].chave;

        graphInsertE(grafo, EDGE(aresta1, aresta2));
    }

    int *dist = malloc(n*sizeof(int));

    graphSearch(grafo, hash[hashU(nomeOrigem)].chave, dist);

    if(dist[destino] != grafo->V){
        printf("%d\n", dist[hash[hashU(nomeDestino)].chave]);
        return 0;
    }
    
    printf("-1\n");

    return 0;
}