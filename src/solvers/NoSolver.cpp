
#include "NoSolver.h"

std::string NoSolver::solve(Game& g) {
    return std::string(g.give_up());
}
