/*parcurgerge graf cu DFS/BFS*/
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} NODE;

typedef struct Graph {
    int vertices;
    int* visited;
    NODE** adjacency_lists;
} GPH;

/* utils */
NODE* create_node(int v) {
    NODE* new_node = malloc(sizeof(NODE));
    if (!new_node) {
        printf("Eroare alocare memorie\n");
        exit(1);
    }
    new_node->data = v;
    new_node->next = NULL;
    return new_node;
}

GPH* create_graph(int vertices) {
    if (vertices <= 0) {
        printf("Numar invalid de noduri\n");
        exit(1);
    }
    GPH* graph = malloc(sizeof(GPH));
    if (!graph) {
        printf("Eroare alocare memorie\n");
        exit(1);
    }
    graph->vertices = vertices;
    graph->adjacency_lists = malloc(vertices * sizeof(NODE*));
    graph->visited = malloc(vertices * sizeof(int));
    if (!graph->adjacency_lists || !graph->visited) {
        printf("Eroare alocare memorie\n");
        exit(1);
    }
    for (int i = 0; i < vertices; i++) {
        graph->adjacency_lists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

void add_edge(GPH* graph, int src, int dest) {
    if (src < 1 || src > graph->vertices || dest < 1 || dest > graph->vertices) {
        printf("Noduri invalide\n");
        return;
    }
    NODE* new_node = create_node(dest - 1);
    new_node->next = graph->adjacency_lists[src - 1];
    graph->adjacency_lists[src - 1] = new_node;

    new_node = create_node(src - 1);
    new_node->next = graph->adjacency_lists[dest - 1];
    graph->adjacency_lists[dest - 1] = new_node;
}

void insert_edges(int nr_of_vertices, int nr_of_edges, GPH* graph) {
    printf("Adauga %d muchii (de la 1 la %d)\n", nr_of_edges, nr_of_vertices);
    for (int i = 0; i < nr_of_edges; i++) {
        int src, dest;
        if (scanf("%d %d", &src, &dest) != 2) {
            printf("Eroare citire muchie\n");
            return;
        }
        add_edge(graph, src, dest);
    }
}

/* bfs utils */
int is_empty(NODE* queue) {
    return queue == NULL;
}

void enqueue(NODE** queue, int data) {
    NODE* new_node = create_node(data);
    if (is_empty(*queue)) {
        *queue = new_node;
    } else {
        NODE* temp = *queue;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

int dequeue(NODE** queue) {
    if (is_empty(*queue)) {
        return -1; // Coada e goală
    }
    NODE* temp = *queue;
    int data = temp->data;
    *queue = (*queue)->next;
    free(temp);
    return data;
}

void wipe_visited_list(GPH* graph, int nr_of_vertices) {
    for (int i = 0; i < nr_of_vertices; i++) {
        graph->visited[i] = 0;
    }
}

/* parcurgeri */
void DFS(GPH* graph, int vertex_nr) {
    if (vertex_nr < 0 || vertex_nr >= graph->vertices) {
        printf("Nod invalid\n");
        return;
    }
    graph->visited[vertex_nr] = 1;
    printf("%d->", vertex_nr + 1); // Afișăm nodul ca 1-based
    NODE* temp = graph->adjacency_lists[vertex_nr];
    while (temp) {
        int connected_vertex = temp->data;
        if (!graph->visited[connected_vertex]) {
            DFS(graph, connected_vertex);
        }
        temp = temp->next;
    }
}

void BFS(GPH* graph, int start) {
    if (start < 0 || start >= graph->vertices) {
        printf("Nod invalid\n");
        return;
    }
    NODE* queue = NULL;
    graph->visited[start] = 1;
    enqueue(&queue, start);
    while (!is_empty(queue)) {
        int current = dequeue(&queue);
        printf("%d ", current + 1); // Afișăm nodul ca 1-based
        NODE* temp = graph->adjacency_lists[current];
        while (temp) {
            int adj_vertex = temp->data;
            if (!graph->visited[adj_vertex]) {
                graph->visited[adj_vertex] = 1;
                enqueue(&queue, adj_vertex);
            }
            temp = temp->next;
        }
    }
}

void free_graph(GPH* graph) {
    if (!graph) return;
    for (int i = 0; i < graph->vertices; i++) {
        NODE* current = graph->adjacency_lists[i];
        while (current) {
            NODE* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(graph->adjacency_lists);
    free(graph->visited);
    free(graph);
}

void BFS(GPH *graph, int start)
{
NODE *queue = NULL;
int main() {
    int nr_of_vertices, nr_of_edges, starting_vertex;

    printf("Cate noduri are graful? ");
    if (scanf("%d", &nr_of_vertices) != 1 || nr_of_vertices <= 0) {
        printf("Numar invalid de noduri\n");
        return 1;
    }

    printf("Cate muchii are graful? ");
    if (scanf("%d", &nr_of_edges) != 1 || nr_of_edges < 0) {
        printf("Numar invalid de muchii\n");
        return 1;
    }

    GPH* graph = create_graph(nr_of_vertices);
    if (!graph) {
        return 1;
    }

    insert_edges(nr_of_vertices, nr_of_edges, graph);

    printf("De unde plecam in DFS? ");
    if (scanf("%d", &starting_vertex) != 1 || starting_vertex < 1 || starting_vertex > nr_of_vertices) {
        printf("Nod invalid\n");
        free_graph(graph);
        return 1;
    }
    printf("Parcurgere cu DFS: ");
    DFS(graph, starting_vertex - 1);
    wipe_visited_list(graph, nr_of_vertices);
    printf("\n");

    printf("De unde plecam in BFS? ");
    if (scanf("%d", &starting_vertex) != 1 || starting_vertex < 1 || starting_vertex > nr_of_vertices) {
        printf("Nod invalid\n");
        free_graph(graph);
        return 1;
    }
    printf("Parcurgere cu BFS: ");
    BFS(graph, starting_vertex - 1);

    free_graph(graph);
    return 0;
}