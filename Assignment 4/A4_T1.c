#include <stdio.h>
#include <stdlib.h>

typedef struct node node;
struct node{
    char vertex;
    struct node *next;
};

typedef struct Graph Graph;
struct Graph{
    int num_vertices;
    int *visited;
    struct node** adjL;
};

typedef struct Queue Queue;
struct Queue{
    int first;
    int last;
    int contents[40];
};

struct node* create_Node(char c){
    struct node *new_node = (node*)malloc(sizeof( struct node));
    new_node->vertex = c;
    new_node->next = NULL;
    return new_node;
}

struct Graph* createGraph(int vertice){
    struct Graph* new_graph = (Graph*)malloc(sizeof(struct Graph));
    new_graph->num_vertices = vertice;
    new_graph->visited = malloc(vertice * sizeof(int));
    new_graph->adjL = malloc(vertice * sizeof(struct Graph));
    
	for (int i=0; i<vertice; i++){
        new_graph->adjL[i] = NULL;
        new_graph->visited[i] = 0;
    }
    return new_graph;
}


void insert_edge(struct Graph* g, char s, char d){
    struct node* new_node = create_Node(d);
    int n = s-65;
    new_node->next = g->adjL[n];
    g->adjL[n] = new_node;
}

void print_adjList(struct Graph* graph){
    printf("\nGraph Adjacency List:\n");
    for (int i = 0; i < graph->num_vertices; i++)
    {
        struct node* temp = graph->adjL[i];
        char v = i + 65; 
        printf("%c", v);
        while (temp)
        {
            printf(" -> ");
            printf("%c", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
    printf("\n");
}

void initialiseVisited(struct Graph *g){
    for (int i=0; i<6; i++){
        g->visited[i] = 0;
    }
    return;
}

void DFS(struct Graph *g, char c){
    int n = c-65;
    g->visited[n] = 1;
    printf("%c ", n+65);

    int num_nodes = 0;
    node* temp = g->adjL[n];
    while(temp){
        num_nodes++;
        temp = temp->next;
    }
	node* curr;
    node* head = g->adjL[n];
    
    int count;
    
    for (int i=0; i<num_nodes; i++){ 
        curr = head;
        count = head->vertex-65;
        while(curr){
            int adjacent = curr->vertex-65;
            if(g->visited[adjacent]==0 && adjacent < count){
                count = adjacent;
            }
            curr = curr->next;
        }
        if(g->visited[count]!=1){
            DFS(g, count+65);
        }
    }
}

struct Queue* create_queue() {
    struct Queue* Q = malloc(sizeof(struct Queue));
    Q->first = -1;
    Q->last = -1;
    return Q;
}


int queue_check(struct Queue* Q) {
    if(Q->last == -1) 
        return 1;
    else 
        return 0;
}

void add_queue(struct Queue* Q, int value){
    if(Q->last == 40-1)
        return;
    else {
        if(Q->first == -1)
            Q->first = 0;
        Q->last++;
        Q->contents[Q->last] = value;
    }
}

int de_queue(struct Queue* q1){
    int i;
    if(queue_check(q1)){
        i = -1;
    }
    else{
        i = q1->contents[q1->first];
        q1->first++;
        if(q1->first > q1->last){
            q1->first = q1->last = -1;
        }
    }
    return i;
}

void BFS(struct Graph *g, char c){
    int n = c-65; 
	int num_nodes = 0;
	
    struct Queue* q1 = create_queue();
    g->visited[n] = 1;
    
    add_queue(q1, n);
    node* temp = g->adjL[n];
    while(temp){
        num_nodes++;
        temp = temp->next;
    }

    while(!queue_check(q1)){
        int curr = de_queue(q1);
        printf("%c ", curr+65);

        node* head = g->adjL[curr];
        node* temp;
        int min;
        
        for (int i=0; i<num_nodes; i++){ 
            temp = head;
            min = head->vertex-65;
            
			while(temp){
                int adjacent = temp->vertex-65;
                
                if(g->visited[adjacent]==0 && adjacent < min){
                    min = adjacent;
                }
                
				temp = temp->next;
            }
            if(g->visited[min]!=1){
            	
                g->visited[min] = 1;
                add_queue(q1, min);
            }
        }
    }
}

int main(){
    struct Graph* g = createGraph(6);

    //Create Graph by inserting edges between nodes
    insert_edge(g, 'A', 'B');
    insert_edge(g, 'A', 'D');
    insert_edge(g, 'A', 'E');
    insert_edge(g, 'B', 'C');
    insert_edge(g, 'B', 'D');
    insert_edge(g, 'C', 'B');
    insert_edge(g, 'C', 'D');
    insert_edge(g, 'D', 'F');
    insert_edge(g, 'E', 'D');
    insert_edge(g, 'F', 'C');

    print_adjList(g);					//Print the adjacency list of each node
    initialiseVisited(g);    
    printf("DFS Results: ");			//DFS with A as the first node
    DFS(g, 'A');
    printf("\n");

    initialiseVisited(g);
    printf("BFS Results: ");			//Run a BFS with A as the first node
    BFS(g, 'A');
    printf("\n");
}
