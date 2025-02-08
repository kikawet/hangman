
#include <string>
#include <unordered_map>
#include <memory>

#ifndef WORDMAP_H
#define WORDMAP_H

class WordMap : public std::unordered_multimap<int, std::string>
{
};

std::unique_ptr<WordMap> loadDictrionary(std::string dictionaryPath);
void print(WordMap& wm);
void print_dbg(WordMap& wm);

#endif // WORDMAP_H
