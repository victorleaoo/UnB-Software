#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hash[5000];
int tamComp = 0;
int maiorComp = 0;
int vis[5000];

// Estrutura do grafo
typedef struct graph{
    int V;
    int E;
    int **adj;
} graph;

// Estrutura de um componente em si
typedef struct comp{
    int init;
    int tam;
} comp;

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

// Inicializa os vetores com 0
void initVetores(){
    memset(vis, 0, sizeof(int)*5000);
    memset(hash, 0, sizeof(int)*5000);
}

void dfsR(graph *G, int v, int u, int conexos){
    vis[u] = 1;
    hash[u] = conexos;

    for(v = 0; v < G->V; v++){
        if(vis[v] == 0 && G->adj[u][v]){
            tamComp++; //tamanho do componente atual
            dfsR(G, u, v, conexos);
        }
    }

    return;
}

int componentesConexos(graph *G, comp *compAtual){
    int conexos = 0;

    for(int i = 0; i < G->V; i++){
        if(vis[i] == 0){
            compAtual[conexos].init = i;
            tamComp = 1;

            dfsR(G, i, i, conexos);
            
            if(tamComp > maiorComp){
                maiorComp = tamComp;
            }

            compAtual[conexos].tam = tamComp;
            conexos++;
        }
    }

    return conexos;
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

void caminho(comp *compAtual, int j, int qntdConex) {
    if(compAtual[hash[j]].tam == maiorComp){
        if(maiorComp != 1){
            printf("Bora pra estrada\n"); //ja esta na maior
        } else{
            printf("Fique em casa\n"); //somente uma
        } 
    } else {
        for(int i = 0; i < qntdConex; i ++) {
            if(compAtual[i].tam == maiorComp) {
                printf("Vamos para %d\n", compAtual[i].init);
                return;
            }
        }
    }

    return;
}

int main() {
    int V, j;
    scanf("%d %d", &V, &j);

    comp *compAtual = malloc(V * sizeof(comp));

    graph *grafo = graphInit(V);

    initVetores();

    int v, w;

    while(scanf("%d %d", &v, &w) != EOF) {
        Edge E = EDGE(v, w);
        graphInsertE(grafo, E);
    }
  
    int qntdConex = componentesConexos(grafo, compAtual);

    caminho(compAtual, j, qntdConex);
  
    return 0;
}