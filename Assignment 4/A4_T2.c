#include <stdio.h>
#include <stdlib.h>
#define SIZE 7

struct graph {
    int** matrix; 
}G;

void insert_edge(struct graph* g, char s, char d, int weight);
void dijkstra_cal(int **graph, int start);
void print_adjMatrix(int vertex);

struct graph *graph_create(int nodes) {

    struct graph * tmp = &G;
    G.matrix = (int **)malloc(nodes * sizeof(int *));
    for (int i=0; i < nodes; i++)	{
         *(G.matrix + i) = (int *)malloc(nodes * sizeof(int));
    }
    for (int i = 0; i <  nodes; i++)
      for (int j = 0; j < nodes; j++)
         G.matrix[i][j] = 0; 

    return tmp;
}
int main(){ 

   struct graph *g = graph_create(SIZE);
    insert_edge(g,'A','B',1);
    insert_edge(g,'A','C',3);
    insert_edge(g,'A','F',10);
    insert_edge(g,'B','G',2);
    insert_edge(g,'B','D',7);
    insert_edge(g,'B','C',1);
    insert_edge(g,'B','E',5);
    insert_edge(g,'C','E',3);
    insert_edge(g,'C','D',9);
    insert_edge(g,'G','D',12);
    insert_edge(g,'D','F',1);
    insert_edge(g,'E','F',2);
    insert_edge(g,'D','E',2);
    dijkstra_cal(g->matrix, 0);
   	return 0; 
}

void dijkstra_cal(int **graph, int start){
 
    int cost[SIZE][SIZE];
	int ini_dist[SIZE];
	int pred[SIZE], perm[SIZE]; 
	int curr, min;
	int  distance, predeccesor;
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            if(graph[i][j] == 0){
                cost[i][j] = 999;
            }
            else{
                cost[i][j] = graph[i][j];
            }
        }
    }
    for(int i = 0; i < SIZE; i++){
        ini_dist[i] = cost[start][i];
        pred[i] = start;
        perm[i] = 0;
    }
    ini_dist[start] = 0;
    perm[start] = 1;
    int count = 1;
    curr = 0;


    printf("\nOrder of Vertices being made permanent: \n");
    print_adjMatrix(start);
    while(count < SIZE){
        min = 999;
        for(int i = 1; i < SIZE; i++){
            distance = ini_dist[curr] + cost[curr][i];
            if(distance < ini_dist[i] && perm[i] == 0){
                ini_dist[i] = distance;
                pred[i] = curr;
            }
            if(min > ini_dist[i] && perm[i] == 0){
                min = ini_dist[i];
                curr = i;
            }
        }
        perm[curr] = 1;
        printf("  was made permanent \n ");
        print_adjMatrix(curr);
        count++;
    }
 
    for(int i = 1; i < SIZE; i++){

        printf("\n\n\n   Distance of vertex ");
        print_adjMatrix(i);
        printf(" from (A) = %d\n", ini_dist[i]);
        printf("Path  = ");
            
        predeccesor = i;
        print_adjMatrix(predeccesor);

        
        while(predeccesor != start){
            predeccesor = pred[predeccesor];
            printf(" <- ");
            print_adjMatrix(predeccesor);
        }
    }
    printf("\n\n");
}
void print_adjMatrix(int vertex){

    char node = (vertex + 65);
    printf("(%c)", node);
}
void insert_edge(struct graph* g, char s, char d, int w){
    g->matrix[s-65][d-65] = w;
    g->matrix[d-65][s-65] = w;
}
