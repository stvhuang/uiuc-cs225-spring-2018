/**
 * @file word_counter.cpp
 * Implementation of the WordFreq class.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Spring 2012
 */

using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::pair;
using std::string;
using std::vector;

template <template <class K, class V> class Dict>
WordFreq<Dict>::WordFreq(const string &infile) : filename(infile) {
    /* nothing */
}

template <template <class K, class V> class Dict>
vector<pair<string, int>> WordFreq<Dict>::getWords(int threshold) const {
    TextFile infile(filename);
    vector<pair<string, int>> ret;

    Dict<std::string, int> hashTable(256);

    while (infile.good()) {
        string word = infile.getNextWord();
        ++hashTable[word];
    }

    for (auto &it : hashTable) {
        if (it.second >= threshold) {
            ret.push_back(it);
        }
    }

    return ret;
}
