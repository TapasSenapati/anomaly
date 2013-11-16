#include <dirent.h>
#include <string>
#include <vector>
#include <stdio.h>
#include <cstdlib>
#include <algorithm>
#include "graphcreate.h"
#include "string.h"

using namespace std;

//utility function to open all the files in the diirectory.
vector<string> open(string path) {

    DIR*    dir;
    dirent* pdir;
    vector<string> files;

    dir = opendir(path.c_str());

    while (pdir = readdir(dir)) {
        if(strcmp(pdir->d_name,".") != 0 && strcmp(pdir->d_name,"..") != 0)
            files.push_back(pdir->d_name);
    }

    return files;
}

//utility function to calculate graph edit distance and plot it.
void ged(vector<string> fileslist)
{
    int no_graphs = fileslist.size();  //this many graphs for which to calcuate ged and plot timeseries
    cout << "no_graphs : " << no_graphs;

    //array to store the graph edit distance for all graphs in timeseries
    int edit_distance[no_graphs-1];



}

int main (int argc, char *argv[])
{
    int userinput;
    string graphdir;

    cout << "\n Run for which graph .. : ";
    cout << "\n 1.as-733 ";
    cout << "\n 2.enron ";
    cout << "\n 3.p2p-Gnutella ";
    cout << "\n 4.reality_mining_voices \n\n";

    cin >> userinput;

    if(userinput == 1)
        graphdir = "./as-733";
    else if(userinput == 2)
        graphdir = "./enron";
    else if(userinput == 3)
        graphdir = "./p2p-Gnutella";
    else
        graphdir = "./reality_mining_voices";

//    int V = 5;
//    int E=7;
//    Graph* graph = createGraph(V,E);
//    addEdge(graph, 0, 1);
//    addEdge(graph, 0, 4);
//    addEdge(graph, 1, 2);
//    addEdge(graph, 1, 3);
//    addEdge(graph, 1, 4);
//    addEdge(graph, 2, 3);
//    addEdge(graph, 3, 4);
//
//    // print the adjacency list representation of the above graph
//    printGraph(graph);
//    delete [] graph;

    vector<string> fileslist;
    fileslist = open(graphdir); // or pass which dir to open

    sort (fileslist.begin(), fileslist.end());

    //for(string i : fileslist)   //print llist of graph files in the directory
        //cout << i << endl;
    ged(fileslist);
    return 0;
}

