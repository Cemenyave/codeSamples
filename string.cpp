#include "string.h"
#include <iostream>

//
//overload of default strlen from ctring
//
inline size_t strlen(const char * str)
{
  unsigned int i = 0;
  while (str[i] != '\0') {
    ++i;
  }
  return i;
}

String::String(void) :
  string()
{
  this->setString("");
}

String::String(const String &str) :
  String()
{
  this->string = str.string;
}

String::String(const char * const str) :
  String()
{
  setString(str);
}

String::String(const char value, const size_t count) :
  string(value, count)
{
  this->string.push('\0');
}

String::~String(void) {}

String &String::operator=(const char *rhv)
{
  setString(rhv);
  return *this;
}

const char &String::operator[](const size_t index) const
{
  assert(index < this->size());
  return this->string[index];
}

char &String::operator[](const size_t index)
{
  return const_cast<char &>(
    static_cast<const String&>(*this)[index]
  );
}

char const * const &String::cstring() const
{
  return this->string.getPtr();
}

char * const &String::cstring()
{
  return const_cast<char * &>(
    static_cast<const String&>(*this).cstring()
  );
}

std::ostream &operator<<(std::ostream& outs, const String &str)
{
  outs << str.cstring();
  return outs;
}

std::istream &operator>>(std::istream& ins, String &S)
{
  char * input = new char[300];
  ins.getline(input, 300);
  int inputLenght = static_cast<int>(strlen(input));
  S.string.resize(inputLenght + 1);
  for (int i = 0; i < inputLenght; ++i) {
    S.string[i] = input[i];
  }
  S.string[inputLenght] = '\0';
  delete[] input;
  return ins;
}

bool operator==(const String &lhs, const String &rhs)
{
  if (lhs.string == rhs.string) {
    return true;
  }

  if (lhs.size() != rhs.size()) {
    return false;
  }

  for (int i = 0; i < lhs.string.size(); ++i)
  {
    if (lhs.string[i] != rhs.string[i])
      return false;
  }
  return true;
}

String &String::operator+(const char *rhs)
{
  size_t len = strlen(rhs);
  if (!len) {
    return *this;
  }

  this->string.insert(rhs, len, this->size());

  return *this;
}

String &String::operator+(const String &rhs)
{
  return (*this) + rhs.cstring();
}

const size_t String::size() const
{
  return this->string.size() - 1;
}

size_t String::find(char needle) const
{
  for (size_t i = 0, s = this->size(); i < s; ++i) {
    if (this->string[i] == needle) {
      return i;
    }
  }
  return npos;
}

size_t String::find(const char * const needle) const
{
  size_t needleLen = strlen(needle);
  if (!needleLen) {
    return npos;
  }

  size_t start = this->find(needle[0]);
  for (size_t i = 1; i < needleLen; ++i) {
    if (this->find(needle[i]) - start > i) {
      return npos;
    }
  }

  return start;
}

size_t String::find(const String &needle) const
{
  return this->find(needle.cstring());
}

String &String::assign(const char * const str, size_t subpos, size_t sublen)
{
  size_t size = strlen(str);
  assert(subpos <= size);
  this->string.set(str + subpos, sublen == npos ? size - subpos : sublen);
  this->string.push('\0');
  return *this;
}

String &String::assign(const String& str, size_t subpos, size_t sublen)
{
  return this->assign(str.cstring(), subpos, sublen);
}

String String::substr(size_t pos, size_t len)
{
  size_t size = this->size();
  if (pos > size) {
    return String();
  }

  return String().assign(*this, pos, len);
}

void String::setString(const char * const &str)
{
  this->string.clear();
  this->string.append(str, strlen(str) + 1/*null terminator*/);
  this->string.shrink();
}
