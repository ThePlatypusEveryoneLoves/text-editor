#include "cpp-terminal/event.hpp"
#include "cpp-terminal/input.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include "editor.hpp"

int main() {
  Editor EditorStatus = InitEditor();
  if (!EditorStatus.OpenEditors.empty()) {
    // TODO: Open files
    std::ifstream is(EditorStatus.OpenEditors[0].file.wholepath);
    std::cout<<EditorStatus.OpenEditors[0].file.wholepath<<std::endl;
    std::string str;
    while (getline(is, str)) {
      std::cout << str << std::endl;
    }
  } else {
    // TODO open default menu
    std::cout<<"Nothing for now...\n";
  }

  while (true) {
    Term::Event event{Term::read_event()};
    switch (event.type()) {
    case Term::Event::Type::Key:
      return 0;
    default:
      continue;
    }
  }
}
