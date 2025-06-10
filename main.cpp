#include "map.hpp"

int main (int argc, char *argv[]) {
  
  Map<int, std::string>m;
  m.insert(2, "foobar");
  m.insert(4, "foo");
  m.insert(1, "bar");

  auto x = m.at(2);

  m[1] = "amar";

  auto y = m.find(1);

  m.print();
  std::cout << x << std::endl;
  std::cout << *y << std::endl;

  Map<int, std::string>m2(m);
  Map<int, std::string>m3(m);
  m2 = m3;

  m2[5] = "fet";
  std::cout << m2[5] << std::endl;


  return 0;
}
