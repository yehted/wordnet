#ifndef SAP_H
#define SAP_H

#include <Digraph\Digraph\Digraph.h>

class SAP {
public:
	SAP();
	SAP(const Digraph& G);
	~SAP();
	SAP(const SAP& other);
	SAP& operator=(const SAP& other);
	int length(int v, int w);
	int length(Bag<int>& v, Bag<int>& w);
	int ancestor(int v, int w);
	int ancestor(Bag<int>& v, Bag<int>& w);
	
private:
	const Digraph* G_;
	int root_;
	int distance_;
};
#endif // !SAP_H