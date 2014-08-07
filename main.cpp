#include "SAP.h"
#include <fstream>
#include <iostream>
#include <cstdio>

int main(int argc, char* argv[]) {
	using namespace std;
	ifstream inFile;
	inFile.open("digraph1.txt");
	//	inFile.open(argv[1]);
	if (!inFile.is_open()) {
		cerr << "File not opened!" << endl;
		exit(1);
	}
	Digraph G(inFile);
	cout << G << endl;
	SAP sap(G);
	int v, w;
	cout << "v: ";
	cin >> v;
	cout << "w: ";
	cin >> w;

	int length = sap.length(v, w);
	int ancestor = sap.ancestor(v, w);
	printf("length = %d, ancestor = %d\n", length, ancestor);

	return 0;
}