#include "WordMap.h"
#include <fstream>
#include <iostream>
#include <map>
#include <set>

std::unique_ptr<WordMap> loadDictrionary(std::string dictionaryPath)
{
    std::ifstream file(dictionaryPath);

    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << dictionaryPath << "\n";
        return std::unique_ptr<WordMap>();
    }

    std::string word;
    std::unique_ptr<WordMap> map = std::make_unique<WordMap>();

    while (!file.eof())
    {
        file >> word;
        map->insert(std::make_pair(word.length(), word));
    }

    return map;
}

void print(WordMap &wm)
{
    std::map<int, int> counts;

    // Count repeated appearences
    for (const auto &[length, word] : wm)
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
        std::cout << "Length " << length << ": " << repetitions << '\n';
}

void print_dbg(WordMap &wm)
{
    std::set<int> keys;

    for (const auto &[key, _] : wm)
    {
        keys.insert(key);
    }

    for (const auto &mapkey : keys)
    {
        const auto &[begin, end] = wm.equal_range(mapkey);

        std::cout << "Length " << mapkey << ": \n";
        for (auto it = begin; it != end; ++it)
            std::cout << "\t│" << it->second << '\n';
    }
}