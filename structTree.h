#ifndef STRUCTTREE_H
#define STRUCTTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Define structures
typedef struct Vertex {
    char label;
    int cost;
} Vertex;

typedef struct Edge {
    int cost;
    Vertex *target;
} Edge;

typedef struct Graph {
    int numVertices;
    Vertex *vertices;
    Edge **adjMatrix;
} Graph;

typedef struct TreeNode {
    Vertex *vertex;
    int edgeCost;
    struct TreeNode *next;
} TreeNode;

typedef struct Tree {
    TreeNode *root;
} Tree;

// Function prototypes
Graph *initializeGraph(int numVertices);
Graph *loadGraphFromFile(const char *filename);
void saveGraphToFile(Graph *graph, const char *filename);
Tree *initializeTree();
void addTreeNode(Tree *tree, Vertex *vertex, int edgeCost);
int getVertexIndexByLabel(Graph *graph, char label);
void displayTree(Tree *tree);
void generateMST(Graph *graph, Tree *tree, int startVertexIndex);
int calculateDistance(Tree *tree, char targetLabel);
void saveTreeToFile(Tree *tree, const char *filename);
Tree *loadTreeFromFile(Graph *graph, const char *filename);

#endif /* STRUCTTREE_H */
