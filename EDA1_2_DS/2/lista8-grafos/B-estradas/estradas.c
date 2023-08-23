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

int vis[5000];

void initVis(){
    memset(vis, 0, sizeof(int)*5000);
}

// Insere Edge na matrix
void graphInsertE(graph *G, Edge e){
    int u = e.u, w = e.w;

    if(G->adj[u][w] == 0){
        G->E++;
    }

    G->adj[u][w] = 1;
    G->adj[w][u] = 1;

    return;
}

void dfsR(graph *G, int v, int u){
    vis[u] = 1;

    for(v = 0; v < G->V; v++){
        if(vis[v] == 0 && G->adj[u][v]){
            dfsR(G, u, v);
        }
    }

    return;
}

int componentesConexos(graph *G){
    int conexos = 0;

    for(int i = 0; i < G->V; i++){
        if(vis[i] == 0){
            dfsR(G, i, i);
            conexos++;
        }
    }

    return conexos;
}

// Adicionar ida e volta no grafo
int main(void){
    int v, u, w;
    
    scanf("%d", &v);

    graph *grafo = graphInit(v);

    initVis();

    while(scanf("%d %d", &u, &w) != EOF){
        Edge E = EDGE(u, w);
        graphInsertE(grafo, E);
    }
    
    printf("%d\n", componentesConexos(grafo));

    return 0;
}