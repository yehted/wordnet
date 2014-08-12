#ifndef WORDNET_H
#define WORDNET_H

#include <SymbolTable\SymbolTable\SeparateChainingHashST.h>
#include <Bag\Bag\Bag.h>
#include <Digraph\Digraph\Digraph.h>
#include "SAP.h"
#include <string>

class WordNet{
public:
	WordNet();
	~WordNet();
	WordNet(const WordNet& other);
	WordNet& operator=(const WordNet& other);
	WordNet(std::string synsets, std::string hypernyms);
	Bag<std::string> nouns();
	bool isNoun(std::string word);
	int distance(std::string nounA, std::string nounB);
	std::string sap(std::string nounA, std::string nounB);

private:
	SeparateChainingHashST<std::string, Bag<int>> st_;
	Bag<std::string> nounset_;
	Digraph G_;
	std::string* synsetArray_;
	int synsetArrayN_;
	SAP wordsap_;
};
#endif // !WORDNET_H