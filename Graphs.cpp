// FILE: graphs.cpp
// Graph Library Implementation File for Asn 6

// including libraries
#include <fstream>		// For reading file from disk
#include <iostream>
#include <string>		// For file name
#include <iomanip>
#include "Edge.h"		// Deinition of an Edge
#include "Graphs.h"
#include <limits>
#include <vector>
using namespace std;

ofstream printer("Result.txt");

// Constructor
Graphs::Graphs()
{
	E = V = order = 0;
}

// Destructor
Graphs::~Graphs()
{
}
// Constructor
void Graphs::print_into_file(string s)
{
	printer << s;
}


// Map vertex number (0,1,2,..) to (A,B,C,..)
char Graphs::Vname(const int s) const
{
	return char(s+65);
}

// Get Graph from text File (file name is stored in string fname)
// Graph is stored in adjacency matrix
void Graphs::getGraph(string fname)		
{
   // Local data ...
	weightType wi;
	ifstream source;

	source.open(fname.c_str()); 
	source >> V;	// Read no. of verices (V)
	// Input weights from the file into a 2-D 
	// Adjacency Matrix of V rows and V columns
	int z; 
	for (int r = 0; r < V; r++)
	{
		for (int j = 0; j < V; j++){

			source >> z; AdjMatrix[r][j] = z;

		}
	}
	source.close();
	getEdges();
	// close file
	
	
}

// Display Adjacency Matrix
void Graphs::dispGraph() const
{
	int i,j;
	for(i=0; i<V; i++)
	{
		for(j=0; j<V; j++)
			printer<<  setw(4)<<AdjMatrix[i][j] << " ";
		printer<< endl;
	}
}

// Get Non-Zero edges from adjacency matrix
// and store them in array edges[]. 
void Graphs::getEdges()			
{
	int r , c;
	int i = 0;
	weightType weight;

	// Only examine weights above the diagonal 
	for (r = 0; r <= V-2; r++)
		for (c = r+1; c <= V-1; c++)
		{
			weight = AdjMatrix[r][c];
			if (weight > 0)
			{
				// save (r,c,weight) in edges[i]
				edges[i].u = r;
				edges[i].v = c;
				edges[i].w = weight;
				i++;
			}
		}

	E = i;		// Number of non-zero edges
	
}

// Get number of vertices (V)	
int Graphs::No_of_Verices() const 				
{
	return V;
}

// Get Number of Non-zero edges (E)
int Graphs::No_of_Edges() const 					
{
	return E;
}

// Shortest paths from node s
// uses Dijkstra's Algorithm

int Graphs:: minDistance(vector<pair<int,string>>dist, bool sptSet[])
{
 
    // Initialize min value
    int min = INT_MAX, min_index;
 
    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v].first <= min)
            min = dist[v].first, min_index = v;
	// returning the result
    return min_index;
}
// Output an edge (e): Vertex names and weight
void Graphs::printEdge(Edge e) const 			
{
	printer << Vname(e.u) << " " << Vname(e.v) << " " << e.w << endl;
}

// Display Graph Edges
void Graphs::dispEdges() const
{
	printer<<"Graph Edges\n";
	for (int i = 0; i < E; i++) 
		printEdge(edges[i]);
}

// Shortest paths from node by utilizing the dijkestra algorithm.
// The idea is to get the node that has the least distance from the source and udpate the paths that we can reach from this node until we finish all of them 
void Graphs::shPath(int src)
{
	vector<pair<int,string>>dist(V); // This vector will hold the shortest distance from source vertex to vertex i.
 
    bool sptSet[V]; // sptSet will hold bolean values; true if vertex i is in shortest the path tree or shortest distance from source to destination is finalized
 
    // Start by setting all distances as INFINITE and stpSet[] will be holding 0 (false) in every index
    for (int i = 0; i < V; i++)
        dist[i].first = INT_MAX, sptSet[i] = false;
 
    // The distance from source to itself is 0
    dist[src].first = 0;
	dist[src].second.push_back(Vname(src));
 
    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        // Choose the vertex of min distance from the set of vertices that are yet to be processed.
        int u = minDistance(dist, sptSet);
 
        // Mark the chosen as processed
        sptSet[u] = true;
 
        // Update distance of the adjacent vertices of that picked vertex.
        for (int v = 0; v < V; v++)
		{string s;
 
            // Update dist[v] if and only if is not in sptSet, there is an edge from u to v, or total weight of the path from src to  v going through u is less than current value of dist[v]
            if (!sptSet[v] && AdjMatrix[u][v]
                && dist[u].first != INT_MAX
                && dist[u].first + AdjMatrix[u][v] < dist[v].first)
                {dist[v].first = dist[u].first + AdjMatrix[u][v];
		via[v]=u;
				}
				}
    }
 
    // print the distance array
    printSolution(dist,src);

}

// Print path vertex from source to destination
void Graphs::printPath(int s, int i) const
{
	// if the source is the same as destination, print the vertex.
	if(i==s){printer <<Vname(s);}
	else{
		printPath(s,via[i]);
		printer <<Vname(i);
	}
}

// print the solution of the shortest path from source to destination of all nodes (vertices)
void  Graphs::printSolution(vector<pair<int,string>>dist,int src)
{
    printer << "Vertex \t\t Distance from Source\t\tPath" << endl;
    for (int i = 0; i < V; i++)
	   {
        printer << Vname(i) << " \t\t\t" << dist[i].first << "\t\t\t";
		printPath(src,i);
		printer<<endl;
	   }
}
// Node Visit Function

// Node Visit Function
void Graphs::visit(int k){ 
	val[k]=++order;
for (int i = 0; i < V; i++)
{
	if (AdjMatrix[k][i]!=0){
if(val[i]==-2)
{
visit(i);
}
	}	
}
}
void Graphs::DFS()									
{ 
int k;
// initialize all values to -2 (unseen)
for ( k = 0; k<V; k++)
{
val[k]=-2;
}
for ( k = 0; k < V; k++)
{
	if(val[k]==-2){visit(k);}
}

}

// print the result of the DFS
void Graphs::showDFS(){
	printer<< "The result of traversing using Depth First Search (DFS):\n";
	for (int i = 0; i < V; i++)
	{
		printer<< Vname(i) << " is the vertex number " <<  to_string(val[i]) << " that was visited\n";
	}
}
