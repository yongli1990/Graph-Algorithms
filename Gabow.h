#ifndef __GABOW_H__
#define __GABOW_H__

#include "graph.h"

class Gabow :public Graph
{
public:
	std::vector< std::vector<unsigned long> > GSCC;
private:
	unsigned long searchOrder;
	std::vector<unsigned long> SCC;
	std::stack<unsigned long> root;
	std::stack<unsigned long> path;
	std::vector<bool> visited;
	std::vector<bool> isPartOfSCC;
	std::vector<unsigned long> DFSOrder;
public:
	Gabow(std::string filePath); //Gabow constructor.
	void resetParams(void);
	void goGabow(unsigned long Index);
};

#endif
