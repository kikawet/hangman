
#include "test_common.h"
#include "solvers/NoSolver.h"

std::u32string solution = U"ARGONAUT";
std::vector<std::u32string> solver_lexicon{solution};
Game g(solver_lexicon);

CTEST(NoSolver, solve)
{
    NoSolver solver;

    ASSERT_U32STR(solution, solver.solve(g));
}