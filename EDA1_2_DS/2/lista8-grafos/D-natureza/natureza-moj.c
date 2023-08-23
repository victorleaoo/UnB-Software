#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int vis[5001];
int hash[5001];
char criaturas[5001][32];

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
    G->adj[w][u] = 1;

    return;
}

void dfsR(graph *G, int start){
    if (vis[start] < 0)
        vis[start] = start;
    for (unsigned i = 0; i < G->V; i++)
        if (G->adj[start][i] != 0 && vis[i] < 0)
        {
            int mn = ((int)i < vis[start] ? (int)i : vis[start]);
            vis[start] = mn;
            vis[i] = mn;
            dfsR(G, i);
        }
        
    return;
}

void initVetores(int c){
    //memset(vis, 0, sizeof(int)*5000);
    //memset(hash, 0, sizeof(int)*5000);
    
    for(int i = 0; i < c; i++){
        vis[i] = -1;
    }

    for(int i = 0; i < c; i++){
        hash[i] = 0;
    }

    return;
}

void solve(){
    int c, r;
    scanf("%d %d", &c, &r);
    if (c == 0 && r == 0){
        return;
    }

    initVetores(c);

    for (int i = 0; i < c; i++){
        scanf(" %s", criaturas[i]);
    }
        
    graph *G = graphInit(c);

    for (int i = 0; i < r; i++){
        char criatura1[32], criatura2[32];
        scanf(" %s %s", criatura1, criatura2);
        
        int ai = -1, bi = -1, j = 0;

        while(j < c && (ai == -1 || bi == -1)){
            // compara até enconntrar uma criatura igual no vetor de criaturas
            if (ai == -1 && strcmp(criaturas[j], criatura1) == 0){
                ai = j;
            } else if (bi == -1 && strcmp(criaturas[j], criatura2) == 0){
                bi = j;
            }

            j++;
        }

        // Daí insere no grafo
        Edge E = EDGE(bi, ai);
        graphInsertE(G, E);
    }

    for (int i = 0; i < c; i++){
        dfsR(G, i);
    }
        
    for (int i = 0; i < G->V; i++)
        free(G->adj[i]);
    free(G->adj);

    int ans = 0;
    for (int i = 0; i < c; i++){
        if (++hash[vis[i]] > ans){
            ans = hash[vis[i]];
        }
    }    

    printf("%d\n", ans);

    solve();
}

int main(){
    solve();

    return 0;
}