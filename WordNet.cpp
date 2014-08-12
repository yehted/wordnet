#include "WordNet.h"
#include <Digraph\Digraph\DirectedCycle.h>
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <sstream>

WordNet::WordNet() {}

WordNet::WordNet(std::string synsets, std::string hypernyms) : synsetArray_(new std::string[4]), synsetArrayN_(4) {
	using namespace std;
	ios::sync_with_stdio(false);
	ifstream::sync_with_stdio(false);
	ifstream synsetIn;
	synsetIn.open(synsets);
	if (!synsetIn.is_open()) {
		cerr << "File not opened!" << endl;
		exit(1);
	}
	int synid = 0;
	string line;
	while (getline(synsetIn, line)) {
		if (line == "") break;
		stringstream synsetSS(line);
		string buffer;
		Deque<string> synsetDQ;
		while (getline(synsetSS, buffer, ','))
			synsetDQ.addFirst(buffer);

		synid = stoi(synsetDQ.removeLast());

		// add synsetName to array for referencing from sap()
		if (synid >= synsetArrayN_) {
			string* synsetArrayCopy = new string[2 * synsetArrayN_];
			for (int i = 0; i < synsetArrayN_; i++)
				synsetArrayCopy[i] = synsetArray_[i];
			delete[] synsetArray_;
			synsetArrayN_ = 2 * synsetArrayN_;
			synsetArray_ = synsetArrayCopy;
		}
		line = synsetDQ.removeLast();
		synsetArray_[synid] = line;
		
		// add all elements of synset into hash table
		stringstream ssin(line);
		Bag<string> synset;
		while (getline(ssin, buffer, ' '))
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
	while (getline(hypernymsIn, line)) {
		if (line == "") break;

		stringstream ssin(line);
		
		string s;
		Deque<int> edges;
		while (getline(ssin, s, ','))
			edges.addFirst(stoi(s));
		
		// Checks parsing is correct
		/*for (int s : edges)
			cout << s << " ";
		cout << endl;*/

		synid = edges.removeLast();
		for (int i : edges)
			G.addEdge(synid, i);
		if (edges.size() > 0) count--;
	}

	hypernymsIn.close();

	// check for cycles
	DirectedCycle finder(G);
	if (finder.hasCycle()) throw std::invalid_argument("Graph contains cycle");

	// check if rooted
	if (count > 1) throw std::invalid_argument("Graph not singly rooted");

	wordsap_ = SAP(G);
}

WordNet::~WordNet() {
	delete[] synsetArray_;
}

WordNet::WordNet(const WordNet& other) : 
	st_(SeparateChainingHashST<std::string, Bag<int>>(other.st_)), 
	nounset_(Bag<std::string>(other.nounset_)),
	G_(other.G_),
	synsetArray_(new std::string[other.synsetArrayN_]),
	synsetArrayN_(other.synsetArrayN_),
	wordsap_(wordsap_) 
{
	for (int i = 0; i < synsetArrayN_; i++)
		synsetArray_[i] = other.synsetArray_[i];
}

WordNet& WordNet::operator=(const WordNet& other) {
	if (&other == this) return *this;
	st_ = other.st_;
	nounset_ = other.nounset_;
	G_ = other.G_;
	synsetArrayN_ = other.synsetArrayN_;
	wordsap_ = other.wordsap_;
	
	delete[] synsetArray_;
	std::string* tempSSA = new std::string[synsetArrayN_];

	for (int i = 0; i < synsetArrayN_; i++)
		tempSSA[i] = other.synsetArray_[i];
	synsetArray_ = tempSSA;

	return *this;
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