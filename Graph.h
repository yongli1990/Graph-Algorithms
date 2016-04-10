#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <fstream>
#include <string>


typedef struct{
	unsigned long sourceID;
	unsigned long destinationID;
}Edge;


class Graph{
public:
	unsigned long vertexsNum;
	unsigned long edgesNum;
	std::vector< std::vector<unsigned long> > adjacentMatrix;
public:
	Graph(std::string filePath); // Graph constructor
};


#endif