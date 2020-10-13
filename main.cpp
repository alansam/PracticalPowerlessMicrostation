#include <iostream>
#include <iomanip>
#include <string>
#include <locale>
#include <codecvt>
#include <cstring>
#include <cctype>

using namespace std::string_literals;

void utf16(std::string);
void utf32(std::string);

int main() {
  std::cout << "PracticalPowerlessMicrostation" << std::endl;

//                   ....+....1....+....2....+....3....+..
  std::string cl =  "aàáâäæãåābcçćčdeèéêëēėęfghiîïíīįìjklł"s
                    "mnñńoôöòóœøōõpqrsßśštuûüùúūvwxyÿzžźż"s;
//                   ..4....+....5....+....6....+....7...
  std::cout << cl.size() << u8'\n' << cl << std::endl;
 
//                   ....+....1....+....2....+....3....+..
  std::string CL =  "AÀÁÂÄÆÃÅĀBCÇĆČDEÈÉÊËĒĖĘFGHIÎÏÍĪĮÌJKLŁ"s
                    "MNÑŃOÔÖÒÓŒØŌÕPQRSŚŠTUÛÜÙÚŪVWXYŸZŽŹŻ"s;      
//                   ..4....+....5....+....6....+....7..
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
  std::cout << '\n' << std::endl;

  utf16(CL);
  utf32(CL);

  utf16(cl);
  utf32(cl);
  
  /*
   *  @see: https://quuxplusone.github.io/blog/2019/02/03/on-teaching-unicode/
   *  @see: https://apps.timwhitlock.info/unicode/inspect/hex/1F468/1F3FF/200D/1F33E
  */
  std::cout 
    << "\xF0\x9F\x91\xA8\xF0\x9F\x8F\xBF\xE2\x80\x8D\xF0\x9F\x8C\xBE"
    << std::endl;
  std::cout 
    << "\xF0\x9F\x91\xA8" << ' '
    << "\xF0\x9F\x8F\xBF" << ' '
    << "\xE2\x80\x8D" << ' '
    << "\xF0\x9F\x8C\xBE"
    << std::endl;
}

void utf16(std::string utf8) {
  std::u16string utf16;
  utf16 = 
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t>{}
    .from_bytes(utf8.data());
  std::cout << "UTF16 conversion produced "
            << utf16.size()
            << " code units:\n";

  size_t lw = 0;
  for (char16_t c_ : utf16) {
    std::cout << std::hex
              << std::setfill('0')
              << std::setw(4)
              << c_
              << ((++lw % 10 == 0) ? '\n' : ' ');
  }
  std::cout << '\n' << std::endl;
}

void utf32(std::string utf8) {
  std::u32string utf32 = std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t>{}.from_bytes(utf8);
  std::cout << "UTF32 conversion produced "
            << std::dec
            << utf32.size()
            << " code units:\n";

  size_t lw = 0;
  for (char32_t c_ : utf32) {
    std::cout << std::hex
              << std::setfill('0')
              << std::setw(8)
              << c_
              << ((++lw % 5 == 0) ? '\n' : ' ');
  }
  std::cout << '\n' << std::endl;
}
