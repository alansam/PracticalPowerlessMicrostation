#include <iostream>
#include <string>
#include <cstring>
#include <cctype>

using namespace std::string_literals;

int main() {
  std::cout << "PracticalPowerlessMicrostation" << std::endl;

//                    ....+....1....+....2....+....3....+..
  std::string cl = u8"aàáâäæãåābcçćčdeèéêëēėęfghiîïíīįìjklł"s
                   u8"mnñńoôöòóœøōõpqrsßśštuûüùúūvwxyÿzžźż"s;
//                    ..4....+....5....+....6....+....7...
  std::cout << cl.size() << u8'\n' << cl << std::endl;
 
//                    ....+....1....+....2....+....3....+..
  std::string CL = u8"AÀÁÂÄÆÃÅĀBCÇĆČDEÈÉÊËĒĖĘFGHIÎÏÍĪĮÌJKLŁ"s
                   u8"MNÑŃOÔÖÒÓŒØŌÕPQRSŚŠTUÛÜÙÚŪVWXYŸZŽŹŻ"s;      
//                    ..4....+....5....+....6....+....7..
  std::cout << CL.size() << u8'\n' << CL << std::endl;

  for (auto cc : cl) {
    std::wcout << cc << L' ';
  }
  std::cout << std::endl;

  for (auto cc : CL) {
    std::wcout << cc << L' ';
  }
  std::cout << std::endl;

  char const * cs = cl.c_str();
  size_t cs_l = std::strlen(cs);
  std::cout << cs_l << ' ' << cl.size() << std::endl;
  for (size_t c_ = 0, pb = 0; c_ < cs_l; ++c_) {
    unsigned char cc = (unsigned char) cs[c_];
    printf("%c [%02x], ",
     (isprint(cc) ? cc : '.'), cc);
    if (++pb % 8 == 0) {
      std::cout << '\n';
    }
  }
  std::cout << std::endl;

  char const * CS = CL.c_str();
  size_t CS_l = std::strlen(CS);
  std::cout << CS_l << ' ' << CL.size() << std::endl;
  for (size_t c_ = 0, pb = 0; c_ < CS_l; ++c_) {
    unsigned char cc = (unsigned char) CS[c_];
    printf("%c [%02x], ",
     (isprint(cc) ? cc : '.'), cc);
    if (++pb % 8 == 0) {
      std::cout << '\n';
    }
  }
  std::cout << std::endl;
}
