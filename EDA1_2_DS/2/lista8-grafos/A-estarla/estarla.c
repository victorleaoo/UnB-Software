#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura do grafo
typedef struct graph{
    int V;
    int E;
    int **adj;
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

// Inicializa matriz
int **MATRIXinit(int V, int init){
    int **matrix = malloc(V*sizeof(int*));

    for(int i = 0; i < V; i++){
        matrix[i] = malloc(V*sizeof(int));
    }

    for(int i = 0; i < V; i++){
        for(int j = 0; j < V; j++){
            matrix[i][j] = init;
        }
    }

    return matrix;
}

// Inicializa grafo
graph *graphInit(int V){
    graph *g = malloc(sizeof(graph));
    g->V = V;
    g->E = 0;
    g->adj = MATRIXinit(V, 0);

    return g;
}

// Insere Edge na matrix
void graphInsertE(graph *G, Edge e){
    int u = e.u, w = e.w;

    if(G->adj[u][w] == 0){
        G->E++;
    }

    G->adj[u][w] = 1;

    return;
}

// Adicionar ida e volta no grafo
int main(void){
    int n, m, j;
    
    scanf("%d %d %d", &n, &m, &j);

    graph *grafo = graphInit(n);

    // Adiciona vizinhos
    int a, vizinho;
    for(int i = 0; i < n; i++){
        scanf("%d", &a);
        for(int j = 0; j < a; j++){
            scanf("%d", &vizinho);
            Edge E = EDGE(i, vizinho);
            graphInsertE(grafo, E);
        }
    }

    int m1;
    for(int i = 0; i < m; i++){
        scanf("%d", &m1);
        grafo->adj[m1][m1] = -1; // já visitou
        for(int j = 0; j < n; j++){
            if(grafo->adj[m1][j] == 1){ // já visitou um cadastrado
                grafo->adj[j][j] = -1;
            }
        }
    }

    int j1;
    for(int i = 0; i < j; i++){
        scanf("%d", &j1);
        if(grafo->adj[j1][j1] == -1){
            printf("Eu vou estar la\n");
        } else{
            printf("Nao vou estar la\n");
        }
    }

    return 0;
}