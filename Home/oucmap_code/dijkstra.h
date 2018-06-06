
#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "Node.h"
#include <queue>
#include <tuple>
#include <stack>
#include <map>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <qvector.h>

class Dijkstra {
public:
	Dijkstra();

	void relax(tuple<int, int, double> edge);
	void dijkstra(int s);
	void computeSP(int source, int vertex);
	void showEWD();

};


#endif // !DIJKSTRA_H
