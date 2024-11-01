
#include <filesystem>
#include <ranges>
#include <vector>
namespace fs = std::filesystem;
struct FileInfo {
  std::string filename;
  std::string filepath;
  std::string wholepath;
};
struct GapBuffer {};
struct EditorState {
  FileInfo file;
  unsigned int CursorX, CursorY;
  std::vector<GapBuffer> FileContents;
};

enum State { VISUAL, NORMAL, INSERT };
struct Editor {
  std::vector<EditorWindow> OpenEditors;
  State CurrState;
  unsigned int Cols, Rows;
  Editor();
  Editor(int, int);
};
