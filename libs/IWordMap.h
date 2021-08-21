#include <unordered_map>
#include <utility>
#include <string>

#ifndef _IWORDMAP
#define _IWORDMAP

template<typename T = std::unordered_multimap<int, std::string>::iterator>
class IWordMap {
  public:
    IWordMap() = delete;
    virtual ~IWordMap() {};
    void insert(std::string word);
    std::pair<T, T> equal_range(int length);
};

#endif