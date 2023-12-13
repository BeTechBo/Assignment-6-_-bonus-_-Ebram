#include <iostream>
#include "Edge.h"
#include"Graphs.cpp"
#include <fstream>
#include <string>


using namespace std;

int main()
{
    Graphs G1 , G2;
    G1.print_into_file("File to be solved: \n");
    G1.getGraph("input_data.txt");
	G1.print_into_file("The number of edges: " + to_string(G1.No_of_Edges()) + '\n');
	G1.print_into_file("The number of vertices: " + to_string(G1.No_of_Verices()) + '\n');
    G1.print_into_file("\nAdjacency matrix\n");
    G1.dispGraph();
    G1.dispEdges();
    G1.shPath(0);
    G1.DFS();
    G1.showDFS();

    G2.print_into_file("\n\nExample file: \n");
    G2.getGraph("test.txt");
	G2.print_into_file("The number of edges: " + to_string(G2.No_of_Edges()) + '\n');
	G2.print_into_file("The number of vertices: " + to_string(G2.No_of_Verices()) + '\n');
    G2.print_into_file("\nAdjacency matrix\n");
    G2.dispGraph();
    G2.dispEdges();
    G2.shPath(0);
    G2.DFS();
    G2.showDFS();

}