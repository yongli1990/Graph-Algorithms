#ifndef __KOSARAJU_H__
#define __KOSARAJU_H__

#include "Graph.h"

class Kosaraju :public Graph
{
private:
	std::vector<bool> visited;
public:
	Kosaraju(std::string filePath);//Kosaraju constructor.
	std::vector< std::vector<unsigned long> > getGSCC_Kosaraju(void);
private:
	void cleanVisitRecord(void);
	std::vector<unsigned long> getFT(void);//Finish time array.
	std::vector< std::vector<unsigned long> > getRvAdjacentMatrix(void);
};


#endif
