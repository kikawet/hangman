#include <iostream>
#include <string>
#include <memory>
#include "libs/Timer.h"
#include "libs/WordMap.h"

Timer timer;

int main()
{
  std::cout << "Loading dictionary...\n";

  timer.start();
  std::unique_ptr<WordMap> map = loadDictrionary("words_alpha_xs.txt");
  timer.end();

  if (!map)
  {
    return EXIT_FAILURE;
  }

  std::cout << "Dictionary loaded (took " << timer.duration() << "ms)\n";

  std::cout << "Dictionary size: " << map->size() << '\n';

  // timer.start();
  // print(*map);
  // timer.end();

  // std::cout << '\n' << *map;

  // std::cout << "Print took "<< timer.duration() <<"ms";

  std::cout << std::endl;

  return EXIT_SUCCESS;
}
