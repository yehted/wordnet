#include "WordNet.h"
#include <Digraph\Digraph\DirectedCycle.h>
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <sstream>

WordNet::WordNet() {}

WordNet::WordNet(std::string synsets, std::string hypernyms) : synsetArray_(new std::string[4]), synsetArrayN_(4) {
	using namespace std;
	ifstream synsetIn;
	synsetIn.open(synsets);
	if (!synsetIn.is_open()) {
		cerr << "File not opened!" << endl;
		exit(1);
	}
	int synid = 0;
	while (!synsetIn.eof()) {
		string line;
		getline(synsetIn, line, ',');
		synid = stoi(line);
		
		// add synsetName to array for referencing from sap()
		if (synid >= synsetArrayN_) {
			string* synsetArrayCopy = new string[2 * synsetArrayN_];
			for (int i = 0; i < synsetArrayN_; i++)
				synsetArrayCopy[i] = synsetArray_[i];
			delete[] synsetArray_;
			synsetArrayN_ = 2 * synsetArrayN_;
			synsetArray_ = synsetArrayCopy;
		}
		getline(synsetIn, line, ',');
		synsetArray_[synid] = line;
		
		// add all elements of synset into hash table
		stringstream ssin(line);
		string buffer;
		Bag<string> synset;
		while (ssin >> buffer)
			synset.add(buffer);

		for (string s : synset) {
			Bag<int> tempsynid;
			// checks if synset element already exists
			if (!st_.contains(s))
				nounset_.add(s);
			else
				tempsynid = st_.get(s);
			tempsynid.add(synid);
			st_.put(s, tempsynid);
		}
	}
	synsetIn.close();
	int count = synid + 1;
	Digraph G(count);

	ifstream hypernymsIn;
	hypernymsIn.open(hypernyms);
	if (!hypernymsIn.is_open()) {
		cerr << "File not opened!" << endl;
		exit(1);
	}

	// Builds Digraph
	while (!hypernymsIn.eof()) {
		string line;
		getline(hypernymsIn, line);
		stringstream ssin(line);
		bool vertex = true;
		string s;
		Bag<int> edges;
		while (getline(ssin, s, ',')){
			if (vertex) {
				synid = stoi(s);
				vertex = false;
			}
			else edges.add(stoi(s));
		}
		for (int i : edges)
			G.addEdge(synid, i);
		if (edges.size() > 1) count--;
	}

	// check for cycles
	DirectedCycle finder(G);
	if (finder.hasCycle()) throw std::invalid_argument("Graph contains cycle");

	// check if rooted
	if (count > 1) throw std::invalid_argument("Graph not singly rooted");

	wordsap_ = SAP(G);
}

Bag<std::string> WordNet::nouns() {
	return nounset_;
}

bool WordNet::isNoun(std::string word) {
	return st_.contains(word);
}

int WordNet::distance(std::string nounA, std::string nounB) {
	if (!isNoun(nounA) || !isNoun(nounB))
		throw std::invalid_argument("Noun(s) not found");

	Bag<int> synsetA = st_.get(nounA);
	Bag<int> synsetB = st_.get(nounB);

	return wordsap_.length(synsetA, synsetB);
}

std::string WordNet::sap(std::string nounA, std::string nounB) {
	if (!isNoun(nounA) || !isNoun(nounB))
		throw std::invalid_argument("Noun(s) not found");

	Bag<int> synsetA = st_.get(nounA);
	Bag<int> synsetB = st_.get(nounB);

	int synid = wordsap_.ancestor(synsetA, synsetB);
	return synsetArray_[synid];
}