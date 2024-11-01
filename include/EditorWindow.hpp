

struct Point{
  unsigned long X, Y;
};
class EditorWindow {
  void virtual render()=0;
  unsigned long width{};
  unsigned long height{};
  Point topLeft{0,0};
};
