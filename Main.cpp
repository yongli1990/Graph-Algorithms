#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <fstream>
#include <string>
#include "Graph.h"
#include "BFS.h"
#include "DFS.h"
#include "Kosaraju.h"
#include "Tarjan.h"
#include "Gabow.h"
#include "Topological.h"
using namespace std;


int main()
{
	const string filePath="Example0.csv";
	cout<<"-------------------Kosaraju Algorithm Test Result-------------------"<<endl;
	Kosaraju KOS(filePath);
	if(!KOS.adjacentMatrix.empty())
	{
		vector< vector<unsigned long> > GSCC=KOS.getGSCC_Kosaraju();
		cout<<"Vertexs num:"<<KOS.vertexsNum<<endl;
		cout<<"Edges num:"<<KOS.edgesNum<<endl;
		cout<<"There are "<<GSCC.size()<<" strongly connected components:"<<endl;
		for(unsigned long i=0; i<GSCC.size(); i++)
		{
			cout<<"SCC"<<i+1<<":"<<endl<<"\t";
			for(unsigned long j=0; j<GSCC[i].size(); j++)
			{
				cout<<GSCC[i][j]<<"\t";
			}
			cout<<endl;
		} 
	}
	cout<<"-------------------Tarjan Algorithm Test Result-------------------"<<endl;
	Tarjan TAR(filePath);
	if(!TAR.adjacentMatrix.empty())
	{
		TAR.resetParams();
		TAR.goTarjan(0);
		cout<<"Vertexs num:"<<TAR.vertexsNum<<endl;
		cout<<"Edges num:"<<TAR.edgesNum<<endl;
		cout<<"There are "<<TAR.GSCC.size()<<" strongly connected components:"<<endl;
		for(unsigned long i=0; i<TAR.GSCC.size(); i++)
		{
			cout<<"SCC"<<i+1<<":"<<endl<<"\t";
			for(unsigned long j=0; j<TAR.GSCC[i].size(); j++)
			{
				cout<<TAR.GSCC[i][j]<<"\t";
			}
			cout<<endl;
		}
	}
	cout<<"-------------------Gabow Algorithm Test Result-------------------"<<endl;
	Gabow GAB(filePath);
	if(!GAB.adjacentMatrix.empty())
	{
		GAB.resetParams();
		GAB.goGabow(0);
		cout<<"Vertexs num:"<<GAB.vertexsNum<<endl;
		cout<<"Edges num:"<<GAB.edgesNum<<endl;
		cout<<"There are "<<GAB.GSCC.size()<<" strongly connected components:"<<endl;
		for(unsigned long i=0; i<GAB.GSCC.size(); i++)
		{
			cout<<"SCC"<<i+1<<":"<<endl<<"\t";
			for(unsigned long j=0; j<GAB.GSCC[i].size(); j++)
			{
				cout<<GAB.GSCC[i][j]<<"\t";
			}
			cout<<endl;
		}
	}
	cout<<"-------------------Topological Sorting Algorithm Test Result-------------------"<<endl;
	Topological TOP(filePath);
	if(!TOP.adjacentMatrix.empty())
	{
		TOP.goTplSorting(0);
		cout<<"Vertexs num:"<<TOP.vertexsNum<<endl;
		cout<<"Edges num:"<<TOP.edgesNum<<endl;
		cout<<"Topological sorting result:"<<endl;
		for(unsigned long i=0; i<TOP.tplSortedVector.size(); i++)
		{
			cout<<TOP.tplSortedVector[i]<<"\t";
		}
		cout<<endl;
	}
	return 0;
}