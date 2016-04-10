#ifndef __TOPOLOGICAL_H__
#define __TOPOLOGICAL_H__

#include "graph.h"


class Topological :public Graph
{
public:
	std::vector<unsigned long> tplSortedVector;
private:
	std::vector<bool> visited;
public:
	Topological(std::string filePath);//Topological-Sorting constructor.
	void goTplSorting(unsigned long startVertex);
private:
	void cleanVisitRecord(void);
};


#endif
