#include <iostream>
#include <iomanip>
#include <string>
#include <locale>
#include <codecvt>
#include <cstring>
#include <cctype>

using namespace std::string_literals;

void utf8(std::string);
void utf16(std::string);
void utf32(std::string);
void txform16(std::string);

/*
 * Transform any std string or string view
 * into any of the 4 the std string types,
 * Apache 2.0 (c) 2018 by DBJ.ORG
 */
template<typename T, typename F>
inline T
  transform_to( F str ) noexcept {
  // note: F has to have the empty() method
  if (str.empty()) {
    return {};
  }
  // note: F must be able to work with std begin and end
   return { std::begin(str), std::end(str) };
  // also the above line requires, T has a constructor
  // that will take begin and end values of type F.
};

int main() {
  std::cout << "PracticalPowerlessMicrostation" << std::endl;

//                   ....+....1....+....2....+....3....+..
  std::string cl =  "aàáâäæãåābcçćčdeèéêëēėęfghiîïíīįìjklł"s
                    "mnñńoôöòóœøōõpqrsßśštuûüùúūvwxyÿzžźż"s;
//                   ..4....+....5....+....6....+....7...
  std::cout << cl.size() << '\n' << cl << std::endl;
 
//                   ....+....1....+....2....+....3....+..
  std::string CL =  "AÀÁÂÄÆÃÅĀBCÇĆČDEÈÉÊËĒĖĘFGHIÎÏÍĪĮÌJKLŁ"s
                    "MNÑŃOÔÖÒÓŒØŌÕPQRSŚŠTUÛÜÙÚŪVWXYŸZŽŹŻ"s;      
//                   ..4....+....5....+....6....+....7..
  std::cout << CL.size() << '\n' << CL << std::endl;

  for (auto cc : cl) {
    std::wcout << cc << L' ';
  }
  std::cout << std::endl;

  for (auto cc : CL) {
    std::wcout << cc << L' ';
  }
  std::cout << std::endl;

  std::string cl1(cl);
  size_t cl1_l = cl1.size();
  std::string CL1(CL);
  size_t CL1_l = CL1.size();
  std::cout << cl1_l << '\n';
  utf8(cl1);
  std::cout << CL1_l << '\n';
  utf8(CL1);

  std::string cl2(cl);
  size_t cl2_l = cl2.size();
  std::string CL2(CL);
  size_t CL2_l = CL2.size();
  std::cout << cl2_l << '\n';
  utf16(cl2);
  std::cout << CL2_l << '\n';
  utf16(CL2);

  std::string cl3(cl);
  size_t cl3_l = cl3.size();
  std::string CL3(CL);
  size_t CL3_l = CL3.size();
  std::cout << cl3_l << '\n';
  utf32(cl3);
  std::cout << CL3_l << '\n';
  utf32(CL3);
  
  std::string cl4(cl);
  size_t cl4_l = cl4.size();
  std::string CL4(CL);
  size_t CL4_l = CL4.size();
  std::cout << cl4_l << '\n';
  txform16(cl4);
  std::cout << CL4_l << '\n';
  txform16(CL4);

  /*
   *  @see: https://quuxplusone.github.io/blog/2019/02/03/on-teaching-unicode/
   *  @see: https://apps.timwhitlock.info/unicode/inspect/hex/1F468/1F3FF/200D/1F33E
  */
  std::cout 
    << "\xF0\x9F\x91\xA8\xF0\x9F\x8F\xBF\xE2\x80\x8D\xF0\x9F\x8C\xBE"s
    << std::endl;
  std::cout 
    << "\xF0\x9F\x91\xA8"s << ' '
    << "\xF0\x9F\x8F\xBF"s << ' '
    << "\xE2\x80\x8D"s     << ' '
    << "\xF0\x9F\x8C\xBE"s
    << std::endl;
}

void utf8(std::string utf8) {
  std::cout << "Function: "s << __func__ << std::endl;

  char const * cs = utf8.c_str();
  size_t utf8_l = std::strlen(cs);
  std::cout << utf8_l << ' ' << utf8.size() << std::endl;
  for (size_t c_ = 0, pb = 0; c_ < utf8_l; ++c_) {
    unsigned char cc = (unsigned char) cs[c_];
    printf("%c [%02x], ",
     (isprint(cc) ? cc : '.'), cc);
    if (++pb % 8 == 0) {
      std::cout << '\n';
    }
  }
  std::cout << std::endl;
}

void utf16(std::string utf8) {
  std::cout << "Function: "s << __func__ << std::endl;

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
  std::cout << "Function: "s << __func__ << std::endl;

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

/*
 *  @see: https://dbj.org/c17-codecvt-deprecated-panic/
 */
void txform16(std::string u8) {
  std::cout << "Function: "s << __func__ << std::endl;

  std::cout << u8.size() << '\n' << u8 << '\n';
  std::u16string u16 = transform_to<std::u16string, std::string>(u8);
  std::cout << "UTF-8 transformed from " << u8.size()
            << " to UTF-16 " << u16.size()
            << '\n';

  size_t lw = 0;
  for (char16_t c_ : u16) {
    std::cout << std::hex
              << std::setfill('0')
              << std::setw(4)
              << c_
              << ((++lw % 10 == 0) ? '\n' : ' ');
  }
  std::cout << '\n' << std::endl;
}
