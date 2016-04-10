#ifndef __DFS_H__
#define __DFS_H__

#include "Graph.h"

class DFS :public Graph
{
private:
	std::vector<bool> visited;
public:
	DFS(std::string filePath);//DFS constructor.
	void goDFS(unsigned long startVertex);
private:
	void cleanVisitRecord(void);
};


#endif