#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Globais
int vis[5000];
int tamComp = 0;
int maiorComp = 0;
int hash[5000];

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

// Estrutura para salvar componentes lidas
typedef struct comp{
    int inicial;
    int tamComp;
} comp;

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

void initVetores(int c){
    //memset(vis, 0, sizeof(int)*5000);
    //memset(hash, 0, sizeof(int)*5000);
    
    for(int i = 0; i < c; i++){
        vis[i] = 0;
    }

    for(int i = 0; i < c; i++){
        hash[i] = 0;
    }

    return;
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

void dfsR(graph *G, int v, int u, int qtdComp){
    vis[u] = 1;
    hash[u] = qtdComp;

    for(v = 0; v < G->V; v++){
        if(vis[v] == 0 && G->adj[u][v]){
            tamComp++; // soma mais um ao tamanho da componente atual
            dfsR(G, u, v, qtdComp);
        }
    }

    return;
}

int countCompConexos(graph *G, comp *compAtual){
    int conexos = 0;

    for(int i = 0; i < G->V; i++){
        if(vis[i] == 0){
            compAtual[conexos].inicial = i;
            tamComp = 1;

            dfsR(G, i, i, conexos);

            if(tamComp > maiorComp){
                maiorComp = tamComp; // nova maior componente
            }

            compAtual[conexos].tamComp = tamComp;
            conexos++;
        }
    }

    return conexos;
}

void solve(){
    int c, r;
    scanf("%d %d", &c, &r);
    if(c == 0 && r == 0){ // final dos casos de teste
        return;
    }

    comp *compAtual = malloc(c*sizeof(comp));

    initVetores(c);

    graph *grafo = graphInit(c);

    char criatura[c][32];
    for(int i = 0; i < c; i++){
        scanf(" %s", criatura[i]);
    }

    char relacao[r*2][32];
    for(int i = 0; i < r*2; i++){
        scanf(" %s", relacao[i]);
    }

    int v, w;
    for(int i = 0; i < r*2; i++){
        for(int j = 0; j < c; j++){
            if(strcmp(relacao[i], criatura[j]) == 0){ // compara criatura com 
                if(i % 2 == 0){
                    v = j;
                    break;
                } else{
                    w = j;
                    Edge E = EDGE(v, w);
                    graphInsertE(grafo, E);
                    break;
                }
            }
        }
    }

    int qtdConexos = countCompConexos(grafo, compAtual);

    printf("%d\n", maiorComp);

    free(grafo);
    free(compAtual);

    solve();
}

// Adicionar ida e volta no grafo
int main(void){
    solve();

    return 0;
}