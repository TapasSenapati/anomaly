#include "graphcreate.h"

int SIZE1 = sizeof(AdjListNode);
int SIZE2 = sizeof(Graph);
int SIZE3 = sizeof(AdjList);

AdjListNode* newAdjListNode(int dest)
{
    AdjListNode* newNode = new AdjListNode[SIZE1];
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int V,int E)
{
    Graph* graph = new Graph[SIZE2];
    graph->V = V;
    graph->E = E;

    // Create an array of adjacency lists.  Size of array will be V
    graph->array = new AdjList[V*SIZE3];

    // Initialize each adjacency list as empty by making head as NULL
    #pragma omp parallel for
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;

    return graph;
}

void addEdge(Graph* graph, int src, int dest)
{
    // Add an edge from src to dest.  A new node is added to the adjacency
    // list of src.  The node is added at the begining
    AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    // Since graph is undirected, add an edge from dest to src also
    newNode = newAdjListNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

void printGraph(Graph* graph)
{
    for (int v = 0; v < graph->V; ++v)
    {
        AdjListNode* pCrawl = graph->array[v].head;
        std::cout << "\n Adjacency list of vertex " << v << "\n head ";
        while (pCrawl)
        {
            std::cout << "-> " << pCrawl->dest;
            pCrawl = pCrawl->next;
        }
        std::cout << std::endl;
    }
}


