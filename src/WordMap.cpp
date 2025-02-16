#include "WordMap.h"
#include <fstream>
#include <iostream>
#include <map>
#include <set>

void WordMap::print(std::ostream &out)
{
    std::map<int, int> counts;

    // Count repeated appearences
    for (const auto &[length, word] : *this)
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
        out << "Length " << length << ": " << repetitions << '\n';
}

void WordMap::print_dbg(std::ostream &out)
{
    std::set<int> keys;

    for (const auto &[key, _] : *this)
    {
        keys.insert(key);
    }

    for (const auto &mapkey : keys)
    {
        const auto &[begin, end] = this->equal_range(mapkey);

        out << "Length " << mapkey << ": \n";
        for (auto it = begin; it != end; ++it)
            out << "\t│" << it->second << '\n';
    }
}