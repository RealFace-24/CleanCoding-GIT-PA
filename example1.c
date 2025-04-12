#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct Graph {
    int vertices;
    int* visited;
    Node** adj_list;
} Graph;

typedef struct Stack {
    int top;
    int capacity;
    int* array;
} Stack;

Node* create_node(int v) {
    Node* new_node = malloc(sizeof(Node));
    if (!new_node) {
        printf("Eroare alocare memorie\n");
        exit(1);
    }
    new_node->data = v;
    new_node->next = NULL;
    return new_node;
}

Graph* create_graph(int vertices) {
    if (vertices <= 0) {
        printf("Numar invalid de noduri\n");
        return NULL;
    }
    Graph* graph = malloc(sizeof(Graph));
    if (!graph) {
        printf("Eroare alocare memorie\n");
        exit(1);
    }
    graph->vertices = vertices;
    graph->adj_list = malloc(vertices * sizeof(Node*));
    graph->visited = malloc(vertices * sizeof(int));
    if (!graph->adj_list || !graph->visited) {
        printf("Eroare alocare memorie\n");
        exit(1);
    }
    for (int i = 0; i < vertices; i++) {
        graph->adj_list[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

void add_edge(Graph* graph, int src, int dest) {
    if (!graph || src < 0 || src >= graph->vertices || dest < 0 || dest >= graph->vertices) {
        printf("Noduri invalide\n");
        return;
    }
    Node* new_node = create_node(dest);
    new_node->next = graph->adj_list[src];
    graph->adj_list[src] = new_node;

    new_node = create_node(src);
    new_node->next = graph->adj_list[dest];
    graph->adj_list[dest] = new_node;
}

void insert_edges(Graph* graph, int edge_count) {
    if (!graph || edge_count < 0) {
        printf("Numar invalid de muchii\n");
        return;
    }
    printf("Introdu %d muchii (de la 0 la %d):\n", edge_count, graph->vertices - 1);
    for (int i = 0; i < edge_count; i++) {
        int src, dest;
        if (scanf("%d %d", &src, &dest) != 2) {
            printf("Eroare citire muchie\n");
            return;
        }
        add_edge(graph, src, dest);
    }
}

int has_direct_edge(Graph* graph, int src, int dest) {
    if (!graph || src < 0 || src >= graph->vertices || dest < 0 || dest >= graph->vertices) {
        return 0;
    }
    Node* current = graph->adj_list[src];
    while (current) {
        if (current->data == dest) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void free_graph(Graph* graph) {
    if (!graph) return;
    for (int i = 0; i < graph->vertices; i++) {
        Node* current = graph->adj_list[i];
        while (current) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(graph->adj_list);
    free(graph->visited);
    free(graph);
}

int main() {
    int vertices, edges, src, dest;

    printf("Cate restaurante (noduri) are reteaua? ");
    if (scanf("%d", &vertices) != 1 || vertices <= 0) {
        printf("Numar invalid de noduri\n");
        return 1;
    }

    printf("Cate drumuri (muchii) are reteaua? ");
    if (scanf("%d", &edges) != 1 || edges < 0) {
        printf("Numar invalid de muchii\n");
        return 1;
    }

    Graph* graph = create_graph(vertices);
    if (!graph) {
        return 1;
    }

    insert_edges(graph, edges);

    printf("Introdu numerele celor doua restaurante de verificat (ex. 0 1): ");
    if (scanf("%d %d", &src, &dest) != 2) {
        printf("Eroare citire noduri\n");
        free_graph(graph);
        return 1;
    }

    if (has_direct_edge(graph, src, dest)) {
        printf("Exista drum direct intre restaurantele %d si %d.\n", src, dest);
    } else {
        printf("Nu exista drum direct intre restaurantele %d si %d.\n", src, dest);
    }

    free_graph(graph);
    return 0;
}