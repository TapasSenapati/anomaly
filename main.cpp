#include <dirent.h>
#include <string>
#include <vector>
#include <stdio.h>
#include <cstdlib>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <set>
#include <unordered_map>
#include <chrono>
#include "graphcreate.h"
#include "string.h"

using namespace std;
typedef std::multimap<int, int> Mymap;

int no_graphs = 100; //total graphs in the directory
string graphdir;
//utility function to open all the files in the diirectory.
vector<string> open(string path)
{

    DIR*    dir;
    dirent* pdir;
    vector<string> files;

    dir = opendir(path.c_str());

    while (pdir = readdir(dir))
    {
        if(strcmp(pdir->d_name,".") != 0 && strcmp(pdir->d_name,"..") != 0)
            files.push_back(pdir->d_name);
    }

    return files;
}

//utility function to calculate graph edit distance and plot it.
void ged(vector<string> fileslist)
{
    //array to store the graph edit distance for all graphs in timeseries
    int edit_distance[no_graphs-1];

    set<int> vetexlist[no_graphs];  //array of set containing list of vertexes for all graphs
    Mymap edgelist[no_graphs];      //map containing the list of edges for all graphs

    int vertexcount[no_graphs];     //total no. of vertices in each graph
    int edgecount[no_graphs];       //total no. of edges in each graph

    //read graphs into memory
    int counter = 0;
    string line;
    for(string filename : fileslist)
    {
        string filepath = graphdir + "/" + filename;
        //cout << "\nfilepath.c_str() : " << filepath.c_str();
        ifstream infile(filepath.c_str());
        int x,y;
        if (infile.good())
        {
            getline(infile,line);
            istringstream iss(line);
            iss >> x >> y;
            vertexcount[counter] = x;
            edgecount[counter] = y;
            //cout << endl << vertexcount[counter] << "  " << edgecount[counter];
            while(getline(infile, line))
            {
                istringstream iss(line);
                iss >> x >> y;
                //cout << endl << x << " " << y;
                vetexlist[counter].insert(x);
                vetexlist[counter].insert(y);
                if(x!=y)
                {
                    edgelist[counter].insert( {x,y});
                    edgelist[counter].insert( {y,x});
                }

            }
            ++counter;
        }
    }

    //for (Mymap::iterator it = edgelist[0].begin();it != edgelist[0].end(); ++it)
    //std::cout << " [" << it->first << ", " << it->second << "]";

    cout << endl;

    for(int j=0; j<no_graphs-1; ++j)
    {
        int Vg = vertexcount[j];
        int Vh = vertexcount[j+1];

        vector<int> common_data;
        set_intersection(vetexlist[j].begin(),vetexlist[j].end(),vetexlist[j+1].begin(),vetexlist[j+1].end(), std::back_inserter(common_data));

        int Vg_Vh = common_data.size();

        int Eg = edgecount[j];
        int Eh = edgecount[j+1];

        int Eg_Eh = 0;

        Mymap::iterator it1 = edgelist[j].begin();
        Mymap::iterator it2 = edgelist[j+1].begin();

        while (it1 != edgelist[j].end() && it2 != edgelist[j+1].end())
        {
            if (it1->first < it2->first)
                ++it1;
            else if (it2->first < it1->first)
                ++it2;
            else     // equal keys
            {
                if(it1->second == it2->second) //equal values
                    Eg_Eh++;
                ++it1;
                ++it2;
            }
        }

        edit_distance[j] = Vg + Vh - (2*Vg_Vh) + Eg + Eh - Eg_Eh;
        //cout << "\nVg " << Vg << " Vh " << Vh << " Vg_Vh " << Vg_Vh << " Eg " << Eg << " Eh " << Eh << " Eg_Eh " << Eg_Eh;
    }

    //save results to file for plotting latter
    // open a file in write mode.
    ofstream outfile;
    outfile.open("graphedit.tsv");
    for(int j=0; j<no_graphs-1; ++j)
        outfile << j+1 << "\t" << edit_distance[j] << endl;
    outfile.close();

}

bool is_not_digit(char c)
{
    return !std::isdigit(c);
}

bool numeric_string_compare(const std::string& s1, const std::string& s2)
{
    // handle empty strings...

    std::string::const_iterator it1 = s1.begin(), it2 = s2.begin();

    if (std::isdigit(s1[0]) && std::isdigit(s2[0]))
    {
        int n1, n2;
        std::stringstream ss(s1);
        ss >> n1;
        ss.clear();
        ss.str(s2);
        ss >> n2;

        if (n1 != n2) return n1 < n2;

        it1 = std::find_if(s1.begin(), s1.end(), is_not_digit);
        it2 = std::find_if(s2.begin(), s2.end(), is_not_digit);
    }

    return std::lexicographical_compare(it1, s1.end(), it2, s2.end());
}

int main (int argc, char *argv[])
{
    int userinput;

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

    cout << "\nWait while ged is being calculated and plotted....";
    vector<string> fileslist;
    fileslist = open(graphdir); // or pass which dir to open

    sort (fileslist.begin(), fileslist.end(),numeric_string_compare);
    no_graphs = fileslist.size();

    //this many graphs for which to calcuate ged and plot timeseries
    //cout << "no_graphs : " << no_graphs;

    //for(string i : fileslist)   //print llist of graph files in the directory
    //cout << i << endl;

    auto start = std::chrono::high_resolution_clock::now();
    ged(fileslist);
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    cout << "\nTime taken to execute the graph edit distance function : " << std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count() << "ms.";
    return 0;
}


