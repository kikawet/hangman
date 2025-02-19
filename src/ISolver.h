
#include <string>
#include "Game.h"

#ifndef SOLVER_H
#define SOLVER_H

class ISolver
{
public:
    virtual std::string solve(Game &game) = 0;
};

#endif // SOLVER_H
