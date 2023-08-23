// Conferir se é um grafo totalmente conexo
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

// Insere Edge na matrix - Só de uma via, dessa vez
void graphInsertE(graph *G, Edge e){
    int u = e.u, w = e.w;

    if(G->adj[u][w] == 0){
        G->E++;
    }

    G->adj[u][w] = 1;

    return;
}

void verificaConex(graph *G, int **conex){
    for(int i = 0; i < G->V; i++){
        for(int j = 0; j < G->V; j++){
            if(G->adj[i][j] != 0){
                conex[i][j] = 1;
            } else{
                conex[i][j] = 0;
            }
        conex[i][i] = 1;
        }
    }

    for(int i = 0; i < G->V; i++){
        for(int j = 0; j < G->V; j++){
            if(conex[j][i] == 1){ // ida e volta verdadeiros
                for(int k = 0; k < G->V; k++){
                    if(conex[i][k] == 1){
                        conex[j][k] = 1;
                    }
                }
            }
        }
    }

    return;
}

void solve(){
    int n, m;
    scanf("%d", &n);
    if(n == 0){
        return;
    }

    scanf("%d", &m);

    graph *G = graphInit(n);

    int v, w, p;
    for(int i = 0; i < m; i++){
        scanf("%d %d %d", &v, &w, &p);
        v--;
        w--;

        Edge E1 = EDGE(v, w);
        graphInsertE(G, E1);
        if(p == 2){ // Dupla mão
            Edge E2 = EDGE(w, v);
            graphInsertE(G, E2);
        }
    }

    int **conex = MATRIXinit(n, 0);

    verificaConex(G, conex);

    for (int i = 0; i < G->V; i++){
        free(G->adj[i]);
    }
    free(G->adj);

    int conexo = 1;
    for(int i = 0; i < n && conexo==1; i++){
        for(int j = 0; j < n && conexo==1; j++){
            if(conex[i][j] == 0){ // se durante toda a matrix de conexão, houver um elemento igual a 0, é não conexo
                conexo = 0;
            }
        }
    }

    printf("%d\n", conexo);

    solve();
}

int main(void){
    solve();

    return 0;
}