#include <Digraph\Digraph\Digraph.h>
#include <limits>

class SAP {
public:
	SAP();
	SAP(const Digraph& G);
	int length(int v, int w);
	int length(Bag<int>& v, Bag<int>& w);
	int ancestor(int v, int w);
	int ancestor(Bag<int>& v, Bag<int>& w);
	
private:
	const int INF = std::numeric_limits<int>::max();
	const Digraph G_;
	int root_;
	int distance_;
};