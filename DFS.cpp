/*
* DFS Algorithm.
* Depth-first search (DFS) is an algorithm for traversing or searching tree or graph data structures.
* One starts at the root (selecting some arbitrary node as the root in the case of a graph)
* and explores as far as possible along each branch before backtracking.
* A version of depth-first search was investigated in the 19th century by
* French mathematician Charles Pierre Tr¨¦maux as a strategy for solving mazes.
*/
#include "DFS.h"
using namespace std;


/*
* DFS constructor.
*/
DFS::DFS(string filePath):Graph(filePath)
{
	for(unsigned long i=0; i<this->vertexsNum; i++)
	{
		this->visited.push_back(false);
	}
}

/*
* Clean visit record.
*/
void DFS::cleanVisitRecord(void)
{
	for(vector<bool>::iterator iter=this->visited.begin(); iter!=this->visited.end(); ++iter)
	{
		(*iter)=false;
	}
}

/*
* Depth-First-Search.
* Fake code:
* A recursive implementation of DFS:
1  procedure DFS(G,v):
2      label v as discovered
3      for all edges from v to w in G.adjacentEdges(v) do
4          if vertex w is not labeled as discovered then
5              recursively call DFS(G,w)
* A non-recursive implementation of DFS:
1  procedure DFS-iterative(G,v):
2      let S be a stack
3      S.push(v)
4      while S is not empty
5            v = S.pop()
6            if v is not labeled as discovered:
7                label v as discovered
8                for all edges from v to w in G.adjacentEdges(v) do
9                    S.push(w)
*/
void DFS::goDFS(unsigned long startVertex)
{
	this->cleanVisitRecord();
	stack<unsigned long> S;
	S.push(startVertex);
	this->visited[startVertex]=true;
	cout<<"Visit:"<<startVertex<<endl;
	while(!S.empty())
	{
		unsigned long rowIndex=0;
		unsigned long columnIndex=0;
		rowIndex=S.top();
		for(columnIndex=0; columnIndex<this->vertexsNum; columnIndex++)
		{
			if(this->adjacentMatrix[rowIndex][columnIndex]!=0 && this->visited[columnIndex]==false)
			{
				cout<<"Visit:"<<columnIndex<<endl;
				this->visited[columnIndex]=true;
				S.push(columnIndex);
				break;
			}
		}
		if(columnIndex==this->vertexsNum)
		{
			S.pop();
		}
	}
}