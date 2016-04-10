/*
* Garph base calss.
*/
#include "Graph.h"
using namespace std;


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
		this->vertexsNum=0;
		this->edgesNum=0;
		this->adjacentMatrix.clear();
		cout<<"Failed to open file !"<<endl;
		cout<<"Instantiation graph failed !"<<endl;
	}
}