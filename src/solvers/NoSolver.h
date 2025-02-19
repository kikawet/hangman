
#include "../ISolver.h"

#ifndef NO_SOLVER_H
#define NO_SOLVER_H

class NoSolver : public ISolver
{
public:
    virtual std::string solve(Game &game);
};

#endif // NO_SOLVER_H