/*
* Kosaraju's Algorithm.
* In computer science, Kosaraju's algorithm (also known as the Kosaraju¨CSharir algorithm)
* is a linear time algorithm to find the strongly connected components of a directed graph.
* Aho, Hopcroft and Ullman credit it to an unpublished paper from 1978 by S. Rao Kosaraju.
* The same algorithm was independently discovered by Micha Sharir and published by him in 1981.
* It makes use of the fact that the transpose graph (the same graph with the direction of every edge reversed)
* has exactly the same strongly connected components as the original graph.
*/
#include "Kosaraju.h"
using namespace std;

/*
* Kosaraju constructor.
*/
Kosaraju::Kosaraju(string filePath):Graph(filePath)
{
	for(unsigned long i=0; i<this->vertexsNum; i++)
	{
		visited.push_back(false);
	}
}

/*
* Clean visit record.
*/
void Kosaraju::cleanVisitRecord(void)
{
	for(vector<bool>::iterator iter=visited.begin(); iter!=visited.end(); ++iter)
	{
		(*iter)=false;
	}
}

/*
* Record the finish time of each node. 
*/
vector<unsigned long> Kosaraju::getFT(void)
{
	cleanVisitRecord();
	vector<unsigned long> FT;
	stack<unsigned long> S;
	unsigned long startVertex=0;
	S.push(startVertex);
	visited[startVertex]=true;
	//DFS.
	while(!S.empty())
	{
		unsigned long rowIndex=0;
		unsigned long columnIndex=0;
		rowIndex=S.top();
		//Traverse.
		for(columnIndex=0; columnIndex<this->vertexsNum; columnIndex++)
		{
			if(this->adjacentMatrix[rowIndex][columnIndex]!=0 && visited[columnIndex]==false)
			{
				visited[columnIndex]=true;
				S.push(columnIndex);
				break;
			}
		}
		//When current node search finished, then pop.
		if(columnIndex==this->vertexsNum)
		{
			//Finished.
			FT.push_back(S.top());
			S.pop();
		}
		//If stack is empty but there are nodes still not found,
		//then set new source node for next search.
		if(S.empty())
		{
			for(unsigned long i=0; i<visited.size()-1; i++)
			{
				if(visited[i]==false)
				{
					S.push(i);
					visited[i]=true;
					break;
				}
			}
		}
	}//DFS finished.
	return FT;
}

/*
* Adjacent matrix transposition.
*/
vector< vector<unsigned long> >  Kosaraju::getRvAdjacentMatrix(void)
{
	vector<unsigned long> vTmp(this->vertexsNum, 0);
	vector< vector<unsigned long> > rvAdjacentMatrix(this->vertexsNum, vTmp);
	for(unsigned long i=0; i<this->vertexsNum; i++)
	{
		for(unsigned long j=0; j<this->vertexsNum; j++)
		{
			rvAdjacentMatrix[i][j]=this->adjacentMatrix[j][i];
		}
	}
	return rvAdjacentMatrix;
}


/*
* Strongly Connected Component-Kosaraju Algorithm.
* If strong components are to be represented by appointing a separate root vertex for each component,
* and assigning to each vertex the root vertex of its component, then Kosaraju's algorithm can be stated as follows:
1. For each vertex u of the graph, mark u as unvisited. Let L be empty.
2. For each vertex u of the graph do Visit(u), where Visit(u) is the recursive subroutine:
	If u is unvisited then:
		1. Mark u as visited.
		2. For each out-neighbour v of u, do Visit(v).
		3. Prepend u to L.
	Otherwise do nothing.
3. For each element u of L in order, do Assign(u,u) where Assign(u,root) is the recursive subroutine:
	If u has not been assigned to a component then:
		1. Assign u as belonging to the component whose root is root.
		2. For each in-neighbour v of u, do Assign(v,root).
	Otherwise do nothing.
*/
vector< vector<unsigned long> > Kosaraju::getGSCC_Kosaraju(void)
{
	vector<unsigned long> SCC;
	vector<unsigned long> FT;
	vector< vector<unsigned long> > GSCC;
	vector< vector<unsigned long> > rvAdjacentMatrix;
	FT=getFT();
	rvAdjacentMatrix=getRvAdjacentMatrix();
	cleanVisitRecord();
	//Search reverse adjacent matrix.
	while(!FT.empty())
	{
		queue<unsigned long> Q;
		SCC.clear();
		unsigned long sourceNode=*(FT.end()-1);
		FT.erase(FT.end()-1);
		Q.push(sourceNode);
		SCC.push_back(sourceNode);
		visited[sourceNode]=true;
		//BFS.
		while(!Q.empty())
		{
			unsigned long rowIndex=0;
			unsigned long columnIndex=0;
			rowIndex=Q.front();
			Q.pop();
			for(columnIndex=0; columnIndex<this->vertexsNum; columnIndex++)
			{
				if(rvAdjacentMatrix[rowIndex][columnIndex]!=0 && visited[columnIndex]==false)
				{
					visited[columnIndex]=true;//Visited.
					Q.push(columnIndex);
					SCC.push_back(columnIndex);
					for(vector<unsigned long>::iterator iter=FT.begin(); iter!=FT.end(); iter++)
					{
						if((*iter)==columnIndex)
						{
							FT.erase(iter);
							break;
						}
					}
				}
			}
		}//BFS Finished.
		GSCC.push_back(SCC);
	}
	return GSCC;
}