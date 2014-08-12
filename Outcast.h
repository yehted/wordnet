#include "WordNet.h"
#include <string>

class Outcast {
public:
	Outcast();
	Outcast(WordNet& wordnet);
	std::string outcast(std::string* nouns, int N);

private:
	WordNet* wordnet_;
};