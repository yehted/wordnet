#include "SAP.h"
#include "WordNet.h"
#include "Outcast.h"
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
	inFile.open("files/digraph1.txt");
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
		//a = "Black_Plague";
		//b = "black_marlin";
		int d = word.distance(a, b);
		string anc = word.sap(a, b);
		cout << d << " = distance between " << a << " and " << b << endl;
		cout << anc << " = common ancestor between " << a << " and " << b << endl;
	}
}

// Outcast test
void Outcast_test() {
	cout << "-- Outcast test --" << endl;
	string synsetsFile = "files/synsets.txt";
	string hypernymsFile = "files/hypernyms.txt";
	WordNet wordnet(synsetsFile, hypernymsFile);
	Outcast outcast(wordnet);

	ifstream inFile;
	string file = "files/outcast11.txt";
	inFile.open(file);
	//	inFile.open(argv[1]);
	if (!inFile.is_open()) {
		cerr << file << " not opened!" << endl;
		exit(1);
	}
	string buffer;
	int N = 0;
	Bag<std::string> bag;
	while (getline(inFile, buffer)) {
		if (buffer == "") break;
		bag.add(buffer);
		N++;
	}
	
	std::string* words = new std::string[N];
	int i = 0;
	for (string s : bag) {
		words[i] = s;
		i++;
	}

	//int N;
	//cout << "Number of words: ";
	//cin >> N;

	//for (int i = 0; i < N; i++) {
	//	cout << "Word " << i + 1 << ": ";
	//	cin >> words[i];
	//}
	//cout << endl;

	cout << "Outcast: " << outcast.outcast(words, N) << endl;
	delete[] words;
}

int main(int argc, char* argv[]) {
//	SAP_test();
//	WordNet_test();
	Outcast_test();
	return 0;
}