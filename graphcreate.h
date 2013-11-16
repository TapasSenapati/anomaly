#ifndef GRAPHCREATE_H_INCLUDED
#define GRAPHCREATE_H_INCLUDED
#include <map>
#include <new>
#include <cstddef>
#include <iostream>
#include <memory>
#include <omp.h>

// A structure to represent an adjacency list node
struct AdjListNode
{
    int dest;
    AdjListNode* next;
};

// A structure to represent an adjacency liat
struct AdjList
{
    AdjListNode *head;  // pointer to head node of list
};

// A structure to represent a graph. A graph is an array of adjacency lists.
// Size of array will be V (number of vertices in graph)
struct Graph
{
    int V;      //number of vertices
    int E;      //number of edges
    AdjList* array;
};

// A utility function to create a new adjacency list node
AdjListNode* newAdjListNode(int dest);

// A utility function that creates a graph of V vertices
Graph* createGraph(int V,int E);

// Adds an edge to an undirected graph
void addEdge(Graph* graph, int src, int dest);

// A utility function to print the adjacenncy list representation of graph
void printGraph(struct Graph* graph);
#endif // GRAPHREAD_H_INCLUDED

