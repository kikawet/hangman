
#include <vector>
#include <cstdlib>

#ifndef RAND_H
#define RAND_H

class Random
{
public:
    template <class T>
    const T &next_item(const std::vector<T> &vec) const
    {
        return vec[rand() % vec.size()];
    }
};

#endif // RAND_H