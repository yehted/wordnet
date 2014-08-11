#include "SAP.h"
#include "WordNet.h"
#include <fstream>
#include <iostream>
#include <cstdio>
#include <string>
#include "vld.h"

using namespace std;

// SAP test
void SAP_test() {
	cout << "-- SAP test --" << endl;
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

}

// WordNet test
void WordNet_test() {
	cout << "-- WordNet test --" << endl;
	string synsetsFile = "files/synsets.txt";
	string hypernymsFile = "files/hypernyms.txt";

	WordNet word(synsetsFile, hypernymsFile);
	string a, b;
	for (int i = 0; i < 3; i++) {
		cout << "First word: ";
		cin >> a;
		cout << "Second word: ";
		cin >> b;
		int d = word.distance(a, b);
		string anc = word.sap(a, b);
		cout << d << " = distance between " << a << " and " << b << endl;
		cout << anc << " = common ancestor between " << a << " and " << b << endl;
	}
}

int main(int argc, char* argv[]) {
//	SAP_test();
	WordNet_test();
	return 0;
}