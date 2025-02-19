#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include "Game.h"

void print_help();

int main()
{
  std::vector<std::string> lexicon = loadLexicon("../lexicons/words_alpha_xl.txt");

  if (lexicon.empty())
  {
    return EXIT_FAILURE;
  }

  std::cout << std::endl;

  Game game(lexicon);
  std::string input;
  bool exit = false;

  while (!exit)
  {
    std::vector<char> guesses = game.guesses();

    std::cout << std::string(guesses.data(), guesses.size()) << std::endl;
    std::cout << hangman_visuals[game.get_failed_count()];
    std::cout << ' ' << game.guessed() << std::endl;
    std::cout << ">";
    std::getline(std::cin, input);
    std::cout << std::string(3, '\n') << std::endl;

    if (input.empty())
      continue;

    if (input == "exit")
      return EXIT_SUCCESS;
    if (input == "help")
    {
      print_help();
      continue;
    }

    bool solved = game.guess(input[0]);
    bool lose = game.get_failed_count() == std::size(hangman_visuals);

    exit = lose || solved;
  }

  std::size_t visual = std::min(std::size(hangman_visuals) - 1, game.get_failed_count());
  std::cout << hangman_visuals[visual];
  std::cout << ' ' << game.guessed() << '\n'
            << std::endl;

  if (game.get_failed_count() == std::size(hangman_visuals))
    std::cout << "YOU FAILED\nSolution was '" << game.give_up() << "'" << std::endl;
  else
    std::cout << "YOU WON" << std::endl;

  return EXIT_SUCCESS;
}

void print_help()
{
  std::cout
      << "━━━━━━━━━━━━━━━━━━━━━━━━━━━\n"
      << "ABEHILU   ──> All guesses  \n"
      << "   ╭───╮                   \n"
      << "   │   │                   \n"
      << "   @   │                   \n"
      << "  🯑│🯒  │                   \n"
      << "  🯑    │                   \n"
      << "       │                   \n"
      << " ══════╧══                 \n"
      << " _ELLO    ──> Word to guess\n"
      << " >C       ──> Next guess   \n"
      << "━━━━━━━━━━━━━━━━━━━━━━━━━━━\n"
      << std::endl;

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}