#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Timer.h"
#include "Game.h"

Timer timer;

int main()
{
  std::cout << "Loading lexicon...\n";

  timer.start();
  std::vector<std::string> lexicon = loadLexicon("../lexicons/words_alpha_xs.txt");
  timer.end();

  if (lexicon.empty())
  {
    return EXIT_FAILURE;
  }

  std::cout << "Lexicon loaded (took " << timer.duration() << "ms)\n";

  std::cout << "Lexicon size: " << lexicon.size() << '\n';

  // timer.start();
  // print(*map);
  // timer.end();

  // std::cout << '\n' << *map;

  // std::cout << "Print took "<< timer.duration() <<"ms";

  std::cout << std::endl;

  return EXIT_SUCCESS;
}
