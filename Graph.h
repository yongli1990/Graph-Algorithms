#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>

using namespace std;


class Graph{
public:
	unsigned long vertexsNum;
	unsigned long edgesNum;
	vector<bool> visited;
	vector< vector<unsigned long> > adjacentMatrix;
public:
	Graph(string filePath); // Graph constructor
	void BFS(unsigned long startVertex);
	void DFS(unsigned long startVertex);
	vector< vector<unsigned long> > getGSCC_Kosaraju();
	vector< vector<unsigned long> > getGSCC_Tarjan();
private:
	void cleanVisitRecord();
	vector<unsigned long> getFT();//Finish time array.
	vector< vector<unsigned long> > getRvAdjacentMatrix();
};




#endif