
#include <vector>
#include <cstdlib>
#include <ctime>

#ifndef RAND_H
#define RAND_H

class Random
{

public:
    Random()
    {
        std::srand(static_cast<unsigned int>(std::time(0)));
    }

    template <class T>
    const T &next_item(const std::vector<T> &vec) const
    {
        return vec[std::rand() % vec.size()];
    }
};

#endif // RAND_H