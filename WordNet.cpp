#include "WordNet.h"
#include <stdexcept>

WordNet::WordNet() {}

WordNet::WordNet(std::string synsets, std::string hypernyms) : synsetArray_(new std::string[4]) {

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