/*
* Topological-Sorting Algorithm.
* Only for Directed-Acyclic-Graph(DAG).
* In the field of computer science, a topological sort (sometimes abbreviated toposort)
* or topological ordering of a directed graph is a linear ordering of its vertices such that
* for every directed edge uv from vertex u to vertex v, u comes before v in the ordering.
* For instance, the vertices of the graph may represent tasks to be performed,
* and the edges may represent constraints that one task must be performed before another;
* in this application, a topological ordering is just a valid sequence for the tasks.
* A topological ordering is possible if and only if the graph has no directed cycles, that is,
* if it is a directed acyclic graph (DAG).Any DAG has at least one topological ordering,
* and algorithms are known for constructing a topological ordering of any DAG in linear time.
*/
#include "Topological.h"
using namespace std;

/*
* Topological-Sorting constructor.
*/
Topological::Topological(string filePath):Graph(filePath)
{
	for(unsigned long i=0; i<this->vertexsNum; i++)
	{
		visited.push_back(false);
	}
}

/*
* Clean visit record.
*/
void Topological::cleanVisitRecord(void)
{
	for(vector<bool>::iterator iter=visited.begin(); iter!=visited.end(); ++iter)
	{
		(*iter)=false;
	}
}

/*
* Topological-Sorting function. 
*/
void Topological::goTplSorting(unsigned long startVertex)
{
	tplSortedVector.clear();
	cleanVisitRecord();
	stack<unsigned long> S;
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
			//Insert current node at the beginning.
			tplSortedVector.insert(tplSortedVector.begin(),S.top());
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
}