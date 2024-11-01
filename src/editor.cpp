#include "editor.hpp"
#include "cpp-terminal/args.hpp"
#include "cpp-terminal/color.hpp"
#include "cpp-terminal/options.hpp"
#include "cpp-terminal/screen.hpp"
#include "cpp-terminal/terminal.hpp"
#include "cpp-terminal/tty.hpp"
#include <iostream>
#include <stdexcept>
Editor::Editor() {
  if (!Term::is_stdin_a_tty()) {
    std::cerr << Term::color_fg(Term::Color::Name::Red)
              << "Error: Terminal input is not connected to a TTY, therefore "
                 "not able to catch any input.\n Please configure your "
                 "terminal or switch terminals}"
              << Term::color_fg(Term::Color::Name::Default);
    throw std::runtime_error("Not TTY");
  }
  Term::terminal.setOptions(Term::Option::ClearScreen,
                            Term::Option::NoSignalKeys, Term::Option::NoCursor,
                            Term::Option::Raw);
  if (Term::Arguments::argc() >= 2) {
    OpenEditors{Term::Arguments::argv() | std::views::drop(1) |
                std::views::transform([](auto const filename) {
                  return EditorState{
                      FileInfo{fs::path{filename}.filename().string(),
                               fs::path{filename}.parent_path().string(),
                               filename},
                      0, 0};
                }) |
                std::ranges::to<std::vector<EditorState>>()};

  } else {
    OpenEditors{};
    Rows{Term::screen_size().rows()};
    Cols{Term::screen_size().columns()};
  }
}
