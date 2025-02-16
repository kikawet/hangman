
#include <string>
#include <unordered_map>
#include <memory>

#ifndef WORDMAP_H
#define WORDMAP_H

class WordMap : public std::unordered_multimap<int, std::string>
{
    void print(std::ostream& out);
    void print_dbg(std::ostream& out);
};

#endif // WORDMAP_H
