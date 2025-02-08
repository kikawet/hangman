#include <unordered_map>
#include <utility>
#include <string>

#ifndef IWORDMAP_H
#define IWORDMAP_H

template<typename T = std::unordered_multimap<int, std::string>::iterator>
class IWordMap {
  public:
    IWordMap() = delete;
    virtual ~IWordMap() {};
    void insert(std::string word);
    std::pair<T, T> equal_range(int length);
};

#endif // IWORDMAP_H