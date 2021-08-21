#include <iostream>
#include <fstream>
#include <unordered_map>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <memory>
#include "libs/Timer.h"
#include "libs/WordMap_MultiMap.h"

using std::string;
using wordMap = std::unordered_multimap<int, string>;

Timer timer;

std::unique_ptr<wordMap> loadDictrionary(string dictionaryPath);
//simple
std::ostream &operator<<(std::ostream &os, const wordMap &map);
//verbose
std::ostream &operator<<(std::ostream &os, const std::unique_ptr<wordMap> &map);

int main(int argc, char *argv[])
{
  std::cout << "Loading dictionary\n";

  timer.start();
  std::unique_ptr<wordMap> map = loadDictrionary("words_alpha_xl.txt");
  timer.end();

  if (!map)
  {
    std::cout << "Dictionary failed loading\n";
    return EXIT_FAILURE;
  }

  std::cout << "Dictionary loaded (took " << timer.duration() << "ms)\n";

  // std::cout << "Dictionary size: " << map->size() << '\n';

  // std::cout << '\n' << *map;

  // std::cout << "Print took "<< timer.duration() <<"ms";

  std::cout << std::endl;

  return EXIT_SUCCESS;
}

std::unique_ptr<wordMap> loadDictrionary(string dictionaryPath)
{
  wordMap map;

  std::ifstream file(dictionaryPath);

  if (!file.is_open())
    return std::make_unique<wordMap>(0);

  std::string word;

  while (!file.eof())
  {
    file >> word;
    map.insert(std::make_pair(word.length(), word));
  }

  return std::make_unique<wordMap>(map);
}

//simple
std::ostream &operator<<(std::ostream &os, const wordMap &map)
{
  timer.start();
  std::map<int, int> counts;

  // Count repeated appearences
  for (const auto &[length, word] : map)
  {
    const auto it = counts.find(length);
    if (it != counts.end())
    {
      ++it->second;
    }
    else
    {
      counts[length] = 1;
    }
  }

  // Print them
  for (const auto &[length, repetitions] : counts)
    os << "Length " << length << ": " << repetitions << '\n';

  timer.end();
  return os;
}

//verbose
std::ostream &operator<<(std::ostream &os, const std::unique_ptr<wordMap> &map)
{
  timer.start();
  std::set<int> keys;

  for (const auto &[key, _] : *map)
  {
    keys.insert(key);
  }

  for (const auto &mapkey : keys)
  {
    const auto &[begin, end] = map->equal_range(mapkey);

    os << "Length " << mapkey << ": \n";
    for (auto it = begin; it != end; ++it)
      os << "\t│" << it->second << '\n';
  }

  timer.end();

  return os;
}