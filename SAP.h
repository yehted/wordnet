#include <Digraph\Digraph\Digraph.h>

class SAP {
public:
	SAP();
	SAP(const Digraph& G);
	int length(int v, int w);
	int length(Bag<int>& v, Bag<int>& w);
	int ancestor(int v, int w);
	int ancestor(Bag<int>& v, Bag<int>& w);
	
private:
	const Digraph G_;
	int root_;
	int distance_;
};