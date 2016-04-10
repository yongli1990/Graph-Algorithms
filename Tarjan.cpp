/*
* Tarjan's Algorithm.
* Tarjan's Algorithm is an algorithm in graph theory for finding the strongly connected components of a graph.
* It runs in linear time, matching the time bound for alternative methods including Kosaraju's algorithm
* and the path-based strong component algorithm. Tarjan's Algorithm is named for its discoverer, Robert Tarjan.
*/
#include "Tarjan.h"
using namespace std;


/*
* Tarjan constructor.
*/
Tarjan::Tarjan(string filePath):Graph(filePath)
{
	searchOrder=0;
	for(unsigned long i=0; i<this->vertexsNum; i++)
	{
		visited.push_back(false);
		isInStack.push_back(false);
		DFSOrder.push_back(ULONG_MAX);
		recallOrder.push_back(ULONG_MAX);
	}
}

/*
* Reset parameters.
*/
void Tarjan::resetParams(void)
{
	searchOrder=0;
	SCC.clear();
	GSCC.clear();
	while(!Stack.empty())
	{
		Stack.pop();
	}
	for(unsigned long i=0; i<this->vertexsNum; i++)
	{
		visited[i]=false;
		isInStack[i]=false;
		DFSOrder[i]=ULONG_MAX;
		recallOrder[i]=ULONG_MAX;
	}
}

/*
* Strongly Connected Component-Tarjan Algorithm.
* SCC must be a subtree of DFS.
* Fake code:
goTarjan(u)
{
	DFSOrder[u]=recallOrder[u]=++searchOrder;
	Stack.push(u);
	foreach (u,v) in Edges
		if(v is not visited)
			goTarjan(v)
			recallOrder[u]=min(recallOrder[u], recallOrder[v])
		else if(v is in stack)
			recallOrder[u]=min(recallOrder[u], DFSOrder[v])
	end foreach

	if(DFSOrder[u]==recallOrder[u])
		repeat
			v=Stack.pop()
			print v
		until (u==v)
	end if

	if(Stack is empty)
		foreach index in visited
			if(visited[index]==false)
				goTarjan(index)
		endforeach
	end if
}
*/
void Tarjan::goTarjan(unsigned long Index)
{
	unsigned long nextIndex=0;
	DFSOrder[Index]=recallOrder[Index]=++searchOrder;
	visited[Index]=true;
	Stack.push(Index);
	isInStack[Index]=true;
	//Recursion DFS.
	for(nextIndex=0; nextIndex<this->vertexsNum; nextIndex++)
	{
		if(this->adjacentMatrix[Index][nextIndex]!=0)
		{
			if(!visited[nextIndex])
			{
				goTarjan(nextIndex); //Recursion.
				recallOrder[Index]= (recallOrder[nextIndex]<recallOrder[Index])? recallOrder[nextIndex]:recallOrder[Index];
			}
			else
			{
				if(isInStack[nextIndex])
				{
					recallOrder[Index]= (DFSOrder[nextIndex]<recallOrder[Index])? DFSOrder[nextIndex]:recallOrder[Index];
				}
			}
		}
	}
	//Pop SCC.
	if(DFSOrder[Index]==recallOrder[Index])
	{
		do
		{
			nextIndex=Stack.top();
			Stack.pop();
			isInStack[nextIndex]=false;
			SCC.push_back(nextIndex);
		}while(nextIndex!=Index);
		GSCC.push_back(SCC);
		SCC.clear();
	}
	//If there are nodes have not been traversed, then continue to traverse.
	if(Stack.empty())
	{
		for(unsigned long i=0; i<this->vertexsNum; i++)
		{
			if(visited[i]==false)
			{
				goTarjan(i);
			}
		}
	}
}