
#include "test_common.h"
#include "solvers/NoSolver.h"

std::string solution = "ARGONAUT";
std::vector<std::string> solver_lexicon{solution};
Game g(solver_lexicon);

CTEST(NoSolver, solve)
{
    NoSolver solver;

    ASSERT_STR(solution.c_str(), solver.solve(g).c_str());
}