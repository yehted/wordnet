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
	cout << "Enter digraph filename: ";
	string file;
	cin >> file;
	ifstream inFile;
	inFile.open(file);
//	inFile.open("files/digraph1.txt");
	if (!inFile.is_open()) {
		cerr << "File not opened!" << endl;
		return;
	}
	Digraph G(inFile);
	cout << G << endl;
	SAP sap(G);
	int v, w;
	cout << "v: (-1 to exit)";
	while (cin >> v) {
		if (v == -1) break;

		cout << "w: ";
		cin >> w;

		int length = sap.length(v, w);
		int ancestor = sap.ancestor(v, w);
		printf("length = %d, ancestor = %d\n", length, ancestor);
		cout << "v: ";
	}
}

// WordNet test
void WordNet_test(WordNet& word) {
	cout << "-- WordNet test --" << endl;
	
	string a, b;
	cout << "Enter words (-1 to quit)" << endl;
	cout << "First word: ";
	while (cin >> a) {
		if (a == "-1") break;

		cout << "Second word: ";
		cin >> b;
		if (!word.isNoun(a) || !word.isNoun(b)) {
			cerr << "Word(s) not found" << endl;
			return;
		}
		//a = "Black_Plague";
		//b = "black_marlin";
		int d = word.distance(a, b);
		string anc = word.sap(a, b);
		cout << d << " = distance between " << a << " and " << b << endl;
		cout << anc << " = common ancestor between " << a << " and " << b << endl;
		cout << "First word: ";
	}
}

// Outcast test
void Outcast_test(WordNet& wordnet) {
	cout << "-- Outcast test --" << endl;
	
	Outcast outcast(wordnet);
	string file;
	cout << "Filename: (exit to quit)";
	while (cin >> file) {
		if (file == "exit") break;
		ifstream inFile;
//		string file = "files/outcast17.txt";
		inFile.open(file);
		//	inFile.open(argv[1]);
		if (!inFile.is_open()) {
			cerr << file << " not opened!" << endl;
			return;
		}
		string buffer;
		int N = 0;
		Bag<std::string> bag;
		while (getline(inFile, buffer)) {
			if (buffer == "") break;
			bag.add(buffer);
			N++;
		}
		inFile.close();

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
		cout << "Filename: ";
	}
}

int main(int argc, char* argv[]) {
	// Loads in the synsets and hypernyms file
	string synsetsFile = "files/synsets.txt";
	string hypernymsFile = "files/hypernyms.txt";
	WordNet wordnet(synsetsFile, hypernymsFile);

	cout << "** WordNet **" << endl;
	cout << "Please choose one of the following: " << endl;
	cout << "1. SAP test" << endl << "2. WordNet test" << endl << "3. Outcast test" << endl;
	int choice;
	cin >> choice;
	switch (choice) {
	case 1:
		SAP_test();
		break;
	case 2:
		WordNet_test(wordnet); 
		break;
	case 3:
		Outcast_test(wordnet);
		break;
	default:
		cout << "Invalid input" << endl;
	}
	cout << "Done!" << endl;

	return 0;
}