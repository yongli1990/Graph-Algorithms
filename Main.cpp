#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <string>
#include "Graph.h"
using namespace std;


int main()
{
	Graph G("Example.csv");
	if(!G.adjacentMatrix.empty())
	{
		vector< vector<unsigned long> > GSCC=G.getGSCC_Kosaraju();
		cout<<"Vertexs num:"<<G.vertexsNum<<endl;
		cout<<"Edges num:"<<G.edgesNum<<endl;
		cout<<"There are "<<GSCC.size()<<" strongly connected component:"<<endl;
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
	return 0;
}
