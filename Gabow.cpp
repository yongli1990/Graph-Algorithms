/*
* Gabow's Algorithm.
* Gabow's Algorithm is an algorithm in graph theory for finding the strongly connected components of a graph.
* Just like Tarjan's algorithm.
* Except that Gabow's Algorithm use a stack(here is "root") to replace the "recallOrder" vector in Tarjan's Algorithm.
*/
#include "Gabow.h"
using namespace std;

/*
* Gabow constructor.
*/
Gabow::Gabow(string filePath):Graph(filePath)
{
	searchOrder=0;
	for(unsigned long i=0; i<this->vertexsNum; i++)
	{
		visited.push_back(false);
		isPartOfSCC.push_back(false);
		DFSOrder.push_back(ULONG_MAX);
	}
}


/*
* Reset parameters.
*/
void Gabow::resetParams(void)
{
	searchOrder=0;
	SCC.clear();
	GSCC.clear();
	while(!root.empty())
	{
		root.pop();
	}
	while(!path.empty())
	{
		path.pop();
	}
	for(unsigned long i=0; i<this->vertexsNum; i++)
	{
		visited[i]=false;
		isPartOfSCC[i]=false;
		DFSOrder[i]=ULONG_MAX;
	}
}


/*
* Strongly Connected Component-Gabow Algorithm.
*/
void Gabow::goGabow(unsigned long Index)
{
	unsigned long nextIndex=0;
	DFSOrder[Index]=++searchOrder;
	root.push(Index);
	path.push(Index);
	visited[Index]=true;
	//Recursion DFS.
	for(nextIndex=0; nextIndex<this->vertexsNum; nextIndex++)
	{
		if(this->adjacentMatrix[Index][nextIndex]!=0)
		{
			if(!visited[nextIndex])
			{
				goGabow(nextIndex); //Recursion.
			}
			else if(isPartOfSCC[nextIndex]==false)
			{
				while(DFSOrder[root.top()]>DFSOrder[nextIndex])
				{
					root.pop();//Stack top stored with root node.
				}
			}
		}
	}
	//Pop SCC.
	if(Index==root.top()) //Current node is a root node.
	{
		root.pop();
		do
		{
			nextIndex=path.top();
			path.pop();
			SCC.push_back(nextIndex);
			isPartOfSCC[nextIndex]=true;
		}while(nextIndex!=Index); //Until backtracking to the root node.
		GSCC.push_back(SCC);
		SCC.clear();
	}
	//If there are nodes have not been traversed, then continue to traverse.
	if(path.empty())
	{
		for(unsigned long i=0; i<this->vertexsNum; i++)
		{
			if(visited[i]==false)
			{
				goGabow(i);
			}
		}
	}
}

