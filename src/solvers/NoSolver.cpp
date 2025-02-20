
#include "NoSolver.h"

std::u32string NoSolver::solve(Game& g) {
    return g.give_up();
}
