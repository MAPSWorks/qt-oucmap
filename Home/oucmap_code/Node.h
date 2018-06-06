
#ifndef TVNODE_H
#define TVNODE_H
#include <string>

using namespace std;

class TVNode {
public:
	int id;
	string name;
	string introduction;

	TVNode(int id = 0, string name = NULL, string introduction = NULL) : id(id), name(name), introduction(introduction) {};

};

#endif // !TVNODE_H
