#include "SAP.h"
#include <limits>
#include <stdexcept>

SAP::SAP() : root_(0), distance_(0) {}

SAP::SAP(const Digraph& G) : root_(0), distance_(0), G_(G), bfdp1_(G), bfdp2_(G) {}

SAP::~SAP() {}

SAP::SAP(const SAP& other) : root_(other.root_), distance_(other.distance_), G_(other.G_),
bfdp1_(other.bfdp1_), bfdp2_(other.bfdp2_) {}

SAP& SAP::operator=(const SAP& other) {
	if (&other == this) return *this;
	G_ = other.G_;
	root_ = other.root_;
	distance_ = other.distance_;
	bfdp1_ = other.bfdp1_;
	bfdp2_ = other.bfdp2_;

	return *this;
}

int SAP::length(int v, int w) {
	if (ancestor(v, w) == -1) return -1;
	return distance_;
}

int SAP::length(Bag<int>& v, Bag<int>& w) {
	if (ancestor(v, w) == -1) return -1;
	return distance_;
}

int SAP::ancestor(int v, int w) {
	if (v < 0 || v >= G_.V() || w < 0 || w >= G_.V())
		throw std::out_of_range("Inputs must be between 0 and V-1");
	
//	BreadthFirstDirectedPaths bfdp1(G_, v);
//	BreadthFirstDirectedPaths bfdp2(G_, w);
	bfdp1_.search(G_, v);
	bfdp2_.search(G_, w);
	root_ = -1;
	distance_ = std::numeric_limits<int>::max();
	for (int i = 0; i < G_.V(); i++) {
		if (bfdp1_.hasPathTo(i) && bfdp2_.hasPathTo(i)) {
			if (bfdp1_.distTo(i) + bfdp2_.distTo(i) < distance_) {
				root_ = i;
				distance_ = bfdp1_.distTo(i) + bfdp2_.distTo(i);
			}
		}
	}
	return root_;
}

int SAP::ancestor(Bag<int>& v, Bag<int>& w) {
	for (int s : v) {
		if (s < 0 || s >= G_.V())
			throw std::out_of_range("Inputs must be between 0 and V-1");
	}
	for (int s : w) {
		if (s < 0 || s >= G_.V())
			throw std::out_of_range("Inputs must be between 0 and V-1");
	}
//	BreadthFirstDirectedPaths bfdp1(G_, v);
//	BreadthFirstDirectedPaths bfdp1(G_, w);
	bfdp1_.search(G_, v);
	bfdp2_.search(G_, w);
	root_ = -1;
	distance_ = std::numeric_limits<int>::max();
	for (int i = 0; i < G_.V(); i++) {
		if (bfdp1_.hasPathTo(i) && bfdp2_.hasPathTo(i)) {
			if (bfdp1_.distTo(i) + bfdp2_.distTo(i) < distance_) {
				root_ = i;
				distance_ = bfdp1_.distTo(i) + bfdp2_.distTo(i);
			}
		}
	}
	return root_;
}