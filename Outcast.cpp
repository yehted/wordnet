#include "Outcast.h"

Outcast::Outcast() {}

Outcast::Outcast(WordNet& wordnet) : wordnet_(&wordnet) {}

std::string Outcast::outcast(std::string* nouns, int N) {
	int max = 0;
	std::string maxword = "";
	for (int i = 0; i < N; i++) {
		int td = 0;
		for (int j = i + 1; j < N; j++)
			td += wordnet_->distance(nouns[i], nouns[j]);
		if (td > max) {
			max = td;
			maxword = nouns[i];
		}
	}
	return maxword;
}