#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <string>
#include <fstream>
#include "Graph.h"

using namespace std;


typedef struct{
	unsigned long sourceID;
	unsigned long destinationID;
}Edge;


/*
* Graph constructor.
*/
Graph::Graph(string filePath)
{
	ifstream csvFile(filePath);
	if(csvFile.is_open())
	{
		const string SEPARATOR=",";
		string strValue;
		string strSourceID;
		string strDestinationID;
		unsigned int sepIndex=0;
		Edge E;
		vector<Edge> allEdges;
		while(csvFile.good())
		{
			csvFile>>strValue;
			sepIndex=strValue.find_first_of(SEPARATOR);
			strSourceID=strValue.substr(0,sepIndex);
			strDestinationID=strValue.substr(sepIndex+1,strValue.size()-1);
			E.sourceID=atoi(strSourceID.c_str());
			E.destinationID=atoi(strDestinationID.c_str());
			allEdges.push_back(E);
		}
		csvFile.close();
		///////////////////////////////////////////////////////////
		map<unsigned long, unsigned long> allVretexs;
		for(vector<Edge>::iterator iterE=allEdges.begin(); iterE!=allEdges.end(); ++iterE)
		{
			allVretexs[(*iterE).sourceID];
			allVretexs[(*iterE).destinationID];
		}
		///////////////////////////////////////////////////////////
		this->vertexsNum=allVretexs.size();
		this->edgesNum=allEdges.size();
		vector<unsigned long> vTmp(this->vertexsNum,0);
		unsigned long x=0,y=0;
		for(unsigned long i=0; i<this->vertexsNum; i++)
		{
			this->visited.push_back(false);
			this->adjacentMatrix.push_back(vTmp);
		}
		for(vector<Edge>::iterator iterE=allEdges.begin(); iterE!=allEdges.end(); ++iterE)
		{
			x=(*iterE).sourceID;
			y=(*iterE).destinationID;
			this->adjacentMatrix[x][y]=1;
		}
	}
	else
	{
		cout<<"Failed to open file !"<<endl;
		cout<<"Instantiation graph failed !"<<endl;
	}
}


/*
* Clean visit record.
*/
void Graph::cleanVisitRecord()
{
	for(vector<bool>::iterator iter=this->visited.begin(); iter!=this->visited.end(); ++iter)
	{
		(*iter)=false;
	}
}


/*
* Breadth-First-Search.
*/
void Graph::BFS(unsigned long startVertex)
{
	this->cleanVisitRecord();
	queue<unsigned long> Q;
	Q.push(startVertex);
	this->visited[startVertex]=true;
	cout<<"Visit:"<<startVertex<<endl;
	while(!Q.empty())
	{
		unsigned long rowIndex=0;
		unsigned long columnIndex=0;
		rowIndex=Q.front();
		Q.pop();
		for(columnIndex=0; columnIndex<this->vertexsNum; columnIndex++)
		{
			if(this->adjacentMatrix[rowIndex][columnIndex]!=0 && this->visited[columnIndex]==false)
			{
				cout<<"Visit:"<<columnIndex<<endl;
				this->visited[columnIndex]=true;
				Q.push(columnIndex);
			}
		}
	}
}


/*
* Depth-First-Search.
*/
void Graph::DFS(unsigned long startVertex)
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


/*
* Adjacent matrix transposition.
*/
vector< vector<unsigned long> >  Graph::getRvAdjacentMatrix()
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
* Record the finish time of each node. 
*/
vector<unsigned long> Graph::getFT()
{
	this->cleanVisitRecord();
	vector<unsigned long> FT;
	stack<unsigned long> S;
	unsigned long startVertex=0;
	unsigned long visitedCounter=0;
	S.push(startVertex);
	this->visited[startVertex]=true;
	visitedCounter++;
	//DFS.
	while( (visitedCounter<this->vertexsNum) || (!S.empty()) )
	{
		unsigned long rowIndex=0;
		unsigned long columnIndex=0;
		if(!S.empty())
		{
			rowIndex=S.top();
		}
		else
		{
			//If stack is empty but there are nodes still not found, then set new nource node for next search.
			for(unsigned long i=0; i<this->visited.size()-1; i++)
			{
				if(this->visited[i]==false)
				{
					this->visited[i]=true;
					visitedCounter++;
					S.push(i);
					rowIndex=S.top();
					break;
				}
			}
		}
		for(columnIndex=0; columnIndex<this->vertexsNum; columnIndex++)
		{
			if(this->adjacentMatrix[rowIndex][columnIndex]!=0 && this->visited[columnIndex]==false)
			{
				this->visited[columnIndex]=true;
				visitedCounter++;
				S.push(columnIndex);
				break;
			}
		}
		if(columnIndex==this->vertexsNum)
		{
			FT.push_back(S.top());//Finished.
			S.pop();
		}
	}//DFS finished.
	cout<<"Finished time(from min to max):"<<endl;
	for(vector<unsigned long>::iterator iter=FT.begin(); iter!=FT.end(); iter++)
	{
		cout<<*iter<<"\t";
	}
	cout<<endl;
	return FT;
}


/*
* Strongly Connected Component-Kosaraju Algorithm.
* Step1: Let G be a directed graph and S be an empty stack.
* Step2: While S does not contain all vertices:
	a:		Choose an arbitrary vertex v not in S. Perform a depth-first search starting at v. 
			Each time that depth-first search finishes expanding a vertex u, push u onto S.
* Step3: Reverse the directions of all arcs to obtain the transpose graph.
* Step4: While S is nonempty:
	a:		Pop the top vertex v from S. Perform a depth-first search starting at v. 
			The set of visited vertices will give the strongly connected component containing v; 
			record this and remove all these vertices from the graph G and the stack S.
			Equivalently, breadth-first search (BFS) can be used instead of depth-first search.
*/
vector< vector<unsigned long> > Graph::getGSCC_Kosaraju()
{
	vector<unsigned long> SCC;
	vector<unsigned long> FT;
	vector< vector<unsigned long> > GSCC;
	vector< vector<unsigned long> > rvAdjacentMatrix;
	FT=this->getFT();
	rvAdjacentMatrix=this->getRvAdjacentMatrix();
	this->cleanVisitRecord();
	//Search reverse adjacent matrix.
	while(!FT.empty())
	{
		queue<unsigned long> Q;
		SCC.clear();
		unsigned long sourceNode=*(FT.end()-1);
		FT.erase(FT.end()-1);
		Q.push(sourceNode);
		SCC.push_back(sourceNode);
		this->visited[sourceNode]=true;
		cout<<"New source node:"<<sourceNode<<endl;
		//BFS.
		while(!Q.empty())
		{
			unsigned long rowIndex=0;
			unsigned long columnIndex=0;
			rowIndex=Q.front();
			Q.pop();
			for(columnIndex=0; columnIndex<this->vertexsNum; columnIndex++)
			{
				if(rvAdjacentMatrix[rowIndex][columnIndex]!=0 && this->visited[columnIndex]==false)
				{
					cout<<"\tVisit node:"<<columnIndex<<endl;
					this->visited[columnIndex]=true;//Visited.
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


/*
* Strongly Connected Component-Tarjan Algorithm.
*/
vector< vector<unsigned long> > Graph::getGSCC_Tarjan()
{
	vector<unsigned long> SCC;
	vector< vector<unsigned long> > GSCC;

	return GSCC;
}