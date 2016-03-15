#pragma once
#ifndef _STRING_IONCE
#define _STRING_IONCE
#include "darray.h"
#include <iosfwd> // forward declaration for std::ostream and std::istream

class String
{
private:
  Darray<char> string;

public:
  String(void);
  String(const String &);
  String(const char *);
  String(const char, const size_t);
  ~String(void);

  //Constants
  static const size_t npos = SIZE_MAX;

  String &operator=(const char *);
  const char &operator[](const size_t) const;
        char &operator[](const size_t);
  friend bool operator==(const String &, const String &);

  String &operator+(const char *);
  String &operator+(const String &);

  ///
  /// Read/write string from/to stream
  ///
  friend std::ostream& operator<<(std::ostream&, const String&);
  friend std::istream& operator>>(std::istream&,       String&);

  ///
  /// Get C-like pointer to string
  ///
  char const * const &cstring() const;
  char * const &cstring();

  ///
  /// Return the lenght of string
  ///
  const size_t size() const;

  ///
  /// Find symbol or substring and return index of first occurrence.
  ///
  size_t find(char) const;
  size_t find(const char * const) const;
  size_t find(const String &) const;

  ///
  /// Assign a part of @str to string from @subpose with length @sublen
  /// If string is shorter then @subpose + @sublen function will assign all
  /// characters until end of @str.
  /// If @sublen is String::npos function will assign all characters until end
  /// of @str.
  ///
  String &assign(const char * const str, size_t subpos = 0, size_t sublen = npos);
  String &assign(const String& str, size_t subpos = 0, size_t sublen = npos);

  ///
  /// Return new wtring made of part of this one.
  /// @pos - begining of substring
  /// @len - lenght of substring (use whole "tail" if ommited)
  ///
  String substr(size_t pos, size_t len = npos);

private:
  void setString(const char * const &);
};

#endif
