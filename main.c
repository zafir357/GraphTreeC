#include <stdio.h>
#include <stdlib.h>
#include "structTree.h"
int main()
{
    Graph *graph = NULL;
    Tree* tree = NULL;
    int startVertexIndex;
    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Charger un graphe\n");
        printf("2. Sauvegarder un graphe\n");
        printf("3. Generer un arbre couvrant à partir du graph charg´\n");
        printf("4. Charger un arbre\n");
        printf("5. Sauvegarder un arbre\n");
        printf("6. Distance d'un point par rapport au point de départ de l'arbre\n");
        printf("7. Quitter\n");
        printf("Choix: ");
        if (scanf("%d", &choice) != 1 || choice < 1 || choice > 7) {//returns 1 only if input is an integer
        // Clear input buffer in case of invalid input
        //verify if input is not a number
        while (getchar() != '\n');
        printf("Entrer Invalid. Il faut un chiffre de 1 à 7.\n");
        continue;  // Skip to next iteration of the loop
        } 

        switch (choice) {
            case 1:
                if (graph != NULL) {
                printf("Un graphe est déjà chargé. Veuillez le décharger avant d'en charger un nouveau.\n");
                } else {
                    graph = loadGraphFromFile("graph.txt");
                    if (graph != NULL) {
                        printf("Graphe chargé avec succés.\n");
                    }
                }
                break;

            case 2:
                if (graph == NULL) {
                    printf("Aucun graphe chargé.\n");
                } else {
                    saveGraphToFile(graph, "saved_graph.txt");
                    printf("Graphe sauvegardé avec succés.\n");
                }
                break;
            case 3:
                if (graph == NULL) {
                    printf("Aucun graphe chargé.\n");
                } else {
                    tree = initializeTree();
                    char startVertexLabel;
                    printf("Entrez le label du sommet de départ pour générer l'arbre couvrant: ");
                    scanf(" %c", &startVertexLabel);
                    int startVertexIndex = getVertexIndexByLabel(graph, startVertexLabel);
                    if (startVertexIndex != -1) {
                        generateMST(graph, tree, startVertexIndex);
                        printf("Arbre couvrant générer avec succés.\n");
                    } else {
                       printf("Le label du sommet de départ n'est pas dans le graphe.\n");
                    }
                }
                break;
            case 4:
                if (tree != NULL) {
                printf("Un arbre est déjà chargé. Veuillez le décharger avant d'en charger un nouveau.\n");
                } else {
                    tree = loadTreeFromFile(graph,"saved_tree.txt");
                    if (tree != NULL) {
                    printf("Arbre chargé avec succès.\n");
                    }
                }
                break;

            case 5:
                if (tree == NULL) {
                    printf("Aucun arbre couvrant générer.\n");
                } else {
                    saveTreeToFile(tree, "saved_tree.txt");
                    printf("Arbre sauvegardé avec succés.\n");
                }
                break;

            case 6:
                if (tree == NULL) {
                    printf("Aucun arbre couvrant générer.\n");
                } else {
                    char targetLabel;
                    printf("Entrez le label du sommet cible: ");
                    scanf(" %c", &targetLabel);
                    int distance = calculateDistance(tree, targetLabel);
                    if (distance == -1) {
                        printf("Le label cible n'est pas dans l'arbre.\n");
                    } else {
                        printf("Distance par rapport au point de départ de l'arbre: %d\n", distance);
                    }
                }
                break;
            case 7:
                if (graph != NULL) {
                    free(graph->vertices);
                    for (int i = 0; i < graph->numVertices; i++) {
                        free(graph->adjMatrix[i]);
                    }
                    free(graph->adjMatrix);
                    free(graph);
                }

                if (tree != NULL) {
                    // Add code to free the tree nodes
                    free(tree);
                }
                printf("Programme terminé.\n");
                return 0;

            default:
                printf("Choix non valide.\n");
                break;
        }
            
    } while (choice != 7);

    return 0;
}