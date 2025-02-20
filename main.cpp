#include <iostream>
#include <codecvt>
#include <locale>
#include <limits>
#include <string>
#include <vector>
#include "Game.h"

void print_help();

int main()
{
  std::vector<std::u32string> lexicon = loadLexicon("../lexicons/words_es_xs.txt");

  if (lexicon.empty())
  {
    return EXIT_FAILURE;
  }

  std::cout << std::endl;

  Game game(lexicon);
  std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
  std::string input;
  bool exit = false;

  while (!exit)
  {
    std::vector<char32_t> guesses = game.guesses();

    std::cout << converter.to_bytes(std::u32string(guesses.data(), guesses.size())) << std::endl;
    std::cout << hangman_visuals[game.get_failed_count()];
    std::cout << ' ' << converter.to_bytes(game.guessed()) << std::endl;
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

    bool solved = game.guess(converter.from_bytes(input)[0]);
    bool lose = game.get_failed_count() == std::size(hangman_visuals);

    exit = lose || solved;
  }

  std::size_t visual = std::min(std::size(hangman_visuals) - 1, game.get_failed_count());
  std::cout << hangman_visuals[visual];
  std::cout << ' ' << converter.to_bytes(game.guessed()) << '\n'
            << std::endl;

  if (game.get_failed_count() == std::size(hangman_visuals))
    std::cout << "YOU FAILED\nSolution was '" << converter.to_bytes(game.give_up()) << "'" << std::endl;
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