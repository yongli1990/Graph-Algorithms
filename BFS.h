#ifndef __BFS_H__
#define __BFS_H__

#include "Graph.h"

class BFS :public Graph
{
private:
	std::vector<bool> visited;
public:
	BFS(std::string filePath);//BFS constructor.
	void goBFS(unsigned long startVertex);
private:
	void cleanVisitRecord(void);
};


#endif