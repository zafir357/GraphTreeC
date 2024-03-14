#include "structTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
// Function to initialize a graph

// Function to initialize a graph
Graph *initializeGraph(int numVertices) {
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->numVertices = numVertices;
    graph->vertices = (Vertex *)malloc(numVertices * sizeof(Vertex));
    graph->adjMatrix = (Edge **)malloc(numVertices * sizeof(Edge *));
    for (int i = 0; i < numVertices; i++) {
        graph->vertices[i].label = 'A' + i;
        graph->vertices[i].cost = 0;
        graph->adjMatrix[i] = (Edge *)malloc(numVertices * sizeof(Edge));
        for (int j = 0; j < numVertices; j++) {
            graph->adjMatrix[i][j].cost = 0;
            graph->adjMatrix[i][j].target = NULL;
        }
    }
    return graph;
}

// 
/*
Function to load a graph from a file
Input Expected: filename, example: graph.txt
output/return type: Graph(with vertices and label)
*/
// Function to load a graph from a file
Graph *loadGraphFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return NULL;
    }

    int numVertices;
    if (fscanf(file, "%d", &numVertices) != 1) {
        printf("Erreur lors de la lecture du nombre de sommets.\n");
        fclose(file);
        return NULL;
    }

    Graph *graph = initializeGraph(numVertices);
    if (graph == NULL) {
        fclose(file);
        return NULL;
    }

    for (int i = 0; i < numVertices; i++) {
        if (fscanf(file, " %c", &(graph->vertices[i].label)) != 1 || !isalpha(graph->vertices[i].label)) {
            printf("Erreur lors de la lecture de l'étiquette du sommet.\n");
            fclose(file);
            return NULL;
        }
        graph->vertices[i].cost = 0;
    }
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            if (fscanf(file, "%d", &(graph->adjMatrix[i][j].cost)) != 1) {
                printf("Erreur lors de la lecture des coûts.\n");
                fclose(file);
                return NULL;
            }
        }
    }

    fclose(file);
    return graph;
}


// Function to save a graph to a file
void saveGraphToFile(Graph *graph, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    fprintf(file, "%d\n", graph->numVertices);

    for (int i = 0; i < graph->numVertices; i++) {
        fprintf(file, "%c ", graph->vertices[i].label);
    }
    fprintf(file, "\n");

    for (int i = 0; i < graph->numVertices; i++) {
        for (int j = 0; j < graph->numVertices; j++) {
            fprintf(file, "%d ", graph->adjMatrix[i][j].cost);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

// Function to initialize a tree
Tree *initializeTree() {
    Tree *tree = (Tree *)malloc(sizeof(Tree));
    tree->root = NULL;
    return tree;
}

// Function to add a tree node
void addTreeNode(Tree *tree, Vertex *vertex, int edgeCost) {
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    newNode->vertex = vertex;
    newNode->edgeCost = edgeCost;
    newNode->next = NULL;

    if (tree->root == NULL) {
        tree->root = newNode;
    } else {
        TreeNode *currentNode = tree->root;
        while (currentNode->next != NULL) {
            currentNode = currentNode->next;
        }
        currentNode->next = newNode;
    }
}

int getVertexIndexByLabel(Graph *graph, char label) {
    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->vertices[i].label == label) {
            return i;
        }
    }
    // Return -1 if the label is not found
    return -1;
}
// Function to display the tree
void displayTree(Tree *tree) {
    TreeNode *currentNode = tree->root;
    while (currentNode != NULL) {
        printf("(%c, %d) -> ", currentNode->vertex->label, currentNode->edgeCost);
        currentNode = currentNode->next;
    }
    printf("NULL\n");
}

// Function to generate the minimum spanning tree using Prim's algorithm
void generateMST(Graph *graph, Tree *tree, int startVertexIndex) {
    int *visited = (int *)malloc(graph->numVertices * sizeof(int));
    for (int i = 0; i < graph->numVertices; i++) {
        visited[i] = 0;
    }
    visited[startVertexIndex] = 1;

    while (1) {
        int minCost = INT_MAX;
        int minSource, minTarget;

        for (int i = 0; i < graph->numVertices; i++) {
            if (visited[i]) {
                for (int j = 0; j < graph->numVertices; j++) {
                    if (!visited[j] && graph->adjMatrix[i][j].cost > 0 && graph->adjMatrix[i][j].cost < minCost) {
                        minCost = graph->adjMatrix[i][j].cost;
                        minSource = i;
                        minTarget = j;
                    }
                }
            }
        }

        if (minCost == INT_MAX) {
            // No more edges to add
            break;
        }

        visited[minTarget] = 1;
        addTreeNode(tree, &(graph->vertices[minTarget]), minCost);
    }
    displayTree(tree);
    free(visited);
}

// Function to calculate the distance of a vertex from the starting vertex in the tree
int calculateDistance(Tree *tree, char targetLabel) {
    TreeNode *currentNode = tree->root;
    int distance = 0;
    while (currentNode != NULL) {
        if (currentNode->vertex->label == targetLabel) {
            return distance;
        }

        distance += currentNode->edgeCost;
        currentNode = currentNode->next;
    }

    // If the target label is not in the tree
    return -1;
}

// Function to save a tree to a file
void saveTreeToFile(Tree *tree, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    TreeNode *currentNode = tree->root;
    while (currentNode != NULL) {
        fprintf(file, "%c %d\n", currentNode->vertex->label, currentNode->edgeCost);
        currentNode = currentNode->next;
    }

    fclose(file);
}

// Function to load a tree from a file
Tree *loadTreeFromFile(Graph *graph,const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return NULL;
    }

    Tree *tree = initializeTree();
    char label;
    int edgeCost;

    while (fscanf(file, " %c %d", &label, &edgeCost) == 2) {
        // Find the corresponding vertex in the graph (you need to have a graph loaded)
        Vertex *targetVertex = NULL;
        for (int i = 0; i < graph->numVertices; i++) {
            if (graph->vertices[i].label == label) {
                targetVertex = &(graph->vertices[i]);
                break;
            }
        }

        // Add the edge to the tree
        if (targetVertex != NULL) {
            addTreeNode(tree, targetVertex, edgeCost);
        }
    }

    fclose(file);
    printf("Tree loaded");
    displayTree(tree);
    return tree;
}
