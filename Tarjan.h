#ifndef __TARJAN_H__
#define __TARJAN_H__

#include "Graph.h"

class Tarjan :public Graph
{
public:
	std::vector< std::vector<unsigned long> > GSCC;
private:
	unsigned long searchOrder;
	std::stack<unsigned long> Stack;
	std::vector<unsigned long> SCC;
	std::vector<bool> visited;
	std::vector<bool> isInStack;
	std::vector<unsigned long> DFSOrder;
	std::vector<unsigned long> recallOrder;
public:
	Tarjan(std::string filePath);// Tarjan constructor.
	void resetParams(void);
	void goTarjan(unsigned long Index);
};

#endif